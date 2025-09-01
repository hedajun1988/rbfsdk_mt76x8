/**
 * @file main.c
 * @author Jio (385426564@qq.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include "rbftest.h"
#include "rbf_api.h"

#if defined(CONFIG_RPC_ENABLE) && (CONFIG_RPC_ENABLE == 1)
#include "rpc.h"
#endif

typedef struct stCmd {
	const char *name;
	void (*func)(char *argv[], int argc);
	const char *desc;
}stCmd_t;


int m_serial_fd = -1;
void* cmd_thread(void* arg);
stCmd_t *cmd_search(const char *cmd);


void do_cmd_help(char *argv[], int argc);
void exit_rbf(char *argv[], int argc);
void test_device(char *argv[], int argc);


stCmd_t all_cmds[] = {
    {"help",do_cmd_help,"help to use"},
    {"enroll",test_enroll,"come in enroll"},
    {"ota",test_ota,"ota start: start ota upgrade"},
    {"subdevota",test_subdev_ota,"subdevota [cat_id][start_no][count]"},
    {"exit",exit_rbf,"exit rbftest"},
    {"setarming",test_setarming,"setarming [enable/disable][start_no][count]"},
    {"findme",test_findme_start,"findme [cat_id][no]"},
    {"stopfindme",test_findme_stop,"stopfindme [cat_id][no]"},
    {"init",init_rbf,"init rbf"},
    {"hub", test_hub, "hub [version][noise][reset]"},
    {"device", test_device, "device [delete][all/cat_id][no]"},
    {"sethub", test_sethub, "sethub [0/1/2/3/4/5] 0:868 1:915 2:433 3:aus 915 4: wpc 868 5:mal 915[custom code]"},
} ;


void do_cmd_help(char *argv[], int argc)
{
    int i = 0;
    for (i = 0; i < sizeof(all_cmds) / sizeof(all_cmds[0]); i++) {
        printf("%-12s\t-\t%s\n", all_cmds[i].name, all_cmds[i].desc);
    }
}
stCmd_t *cmd_search(const char *cmd)
{
    int i = 0;
    for (i = 0; i < sizeof(all_cmds) / sizeof(all_cmds[0]); i++) {
        if (strcmp(all_cmds[i].name, cmd) == 0) {
            return &all_cmds[i];
        }
    }
    return NULL;
}

int parse_argv(char **argv, int argv_len, char *buf)
{
    int argc = 0;
    char *cp = buf;
    char *dest = buf;
    char quote;
    char c;

    while (argc < argv_len && *cp != '\0') {
        /*
         * Skip leading blanks and tabs.
         */
        while ((c = *cp) != '\0' && (c == ' ' || c == '\t')) {
            cp++;
        }

        if (c == '\0') {
            break;
        }

        /*
         * copy arg and skip until next blank, tab, or end of string.
         * If quoted, look for matching quote.
         */
        quote = 0;
        *argv++ = cp;
        argc++;
        for (dest = cp; (c = *cp) != '\0'; cp++) {
            if (quote) {
                if (c == quote)  {
                    quote = 0;
                    continue;
                }
            } else {
                /*
                 * Look for start quote.
                 */
                if (c == '\'' || c == '\"') {
                    quote = c;
                    continue;
                }

                if (c == ' ' || c == '\t') {
                    break;
                }
            }
            *dest++ = c;
        }

        *dest = '\0';
        if (c == '\0') {
            break;
        }
        cp++;
    }

    if (argc < argv_len) {
        *argv = 0;
    }
    return argc;
}
void cmd_in_buffer(char *buf, int size, int type)
{

    if (strcmp(buf, "") != 0) {
        char *argv[20];
        int argc;
        argc = parse_argv(argv, sizeof(argv), buf);

        //stCmd_t *cmd = cmd_search(argv[0]);
        char* cmd = argv[0];
        if (cmd == NULL) {
            printf("invalid cmd!");
        } else {
            stCmd_t *cmd = cmd_search(argv[0]);
            if (cmd == NULL) {
                printf("invalid cmd!");
            } else {
                // cmd->func(argv, argc);
                if (argc > 0) {
                    cmd->func(&argv[1], argc-1);
                }
            }

            //int num = atoi(cmd);
            //func(num);
            // do something
        }
    } else {
        //fprintf(stdout,"get:%s\n",buf);
    }
    fprintf(stdout, "%s\r\n", "$");
}

void cmd_in(void *arg, int fd)
{
    char buf[1024];
    int size = 0;

    int ret = read(fd, buf, sizeof(buf));
    if (ret < 0) {
        printf("what happend?");
        return;
    }

    if (ret == 0) {
        printf("error!");
        return;
    }

    size = ret;
    buf[size] = 0;
    if (size >= 1 && buf[size - 1] == '\n') {
        buf[size - 1] = 0;
        size--;
    }

    char *p = buf;
    while (*p == ' ') {
        p++;
        size--;
    }

    if (size > 0) {
        memcpy(buf, p, size);
    }  else {
        buf[0] = 0;
        size = 0;
    }

    cmd_in_buffer(buf, size, 1);
}


void* cmd_thread(void* arg) {

    while (1) {
        /**> loop */
		int maxfd = 0;
		fd_set	fds;
		FD_ZERO(&fds);

        FD_SET(0, &fds);
        maxfd =1;

        struct timeval	tv;
        tv.tv_sec = 1;
        int ret = select(maxfd + 1, &fds, NULL, NULL, &tv);
		if (ret == 0) {
			continue;
		} else if (ret < 0) {
            break;
        }

        if(FD_ISSET(0, &fds)) {
            cmd_in((void *)1,0);
        }
    }
}

int rbf_port_setup()
{
    struct termios setup_termios;

    m_serial_fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (m_serial_fd < 0) {
        return -1;
    }

    fcntl(m_serial_fd,F_SETFL,0);
    tcgetattr(m_serial_fd,&setup_termios);

    setup_termios.c_cflag |= CLOCAL;
    setup_termios.c_cflag |= CREAD;
    setup_termios.c_cflag &= ~CSIZE;
    setup_termios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    setup_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    setup_termios.c_oflag &= ~(OPOST);

    cfsetispeed(&setup_termios, B115200);
    cfsetospeed(&setup_termios, B115200);

    setup_termios.c_cflag |= CS8;
    setup_termios.c_cflag &= ~PARENB;
    setup_termios.c_iflag &= ~INPCK;
    setup_termios.c_cflag &= ~CSTOPB;  

    setup_termios.c_cc[VTIME] = 0;  
    setup_termios.c_cc[VMIN] = 0;  

    tcflush(m_serial_fd, TCIFLUSH);
    tcsetattr(m_serial_fd, TCSANOW, &setup_termios);

    return 0;
}


static int rbf_port_read(unsigned char *buf, int bufsize, int timeout)
{
    fd_set rset; 
    struct timeval _timeout;

    if (m_serial_fd < 0) {
        return -1;
    }

    if (timeout > 0) {

        FD_ZERO(&rset);
        FD_SET(m_serial_fd,&rset);

        _timeout.tv_sec = (time_t)(timeout / 1000); 
        _timeout.tv_usec = 0;                      
        int retval = select(m_serial_fd + 1,&rset, NULL, NULL, &_timeout);

        if(retval <= 0) {
            return 0;
        }
        
    }

    int len = read(m_serial_fd, buf, bufsize);
    return len;
}

static int rbf_port_write(unsigned char *data, int dataLen)
{
    if (m_serial_fd < 0) {
        return -1;
    }

    return write(m_serial_fd, (const char *) data, dataLen);
}

static void rbf_port_reset()
{
    system("echo 1 > /sys/class/gpio/gpio22/value");
    usleep(100*1000);
    system("echo 0 > /sys/class/gpio/gpio22/value");
}

int app_rbf_port_config(void)
{
    RBF_port_t rbf_port = {0};

    rbf_port_setup();

    rbf_port.read = &rbf_port_read;
    rbf_port.write = &rbf_port_write;
    rbf_port.reset = &rbf_port_reset;

    rbf_set_port(&rbf_port);
    return 0;
}

int main()
{
    pthread_t stThread;

    printf("rbf sdk version: %d.%d.%d\n", RB_SDK_VERSION, RB_SDK_REVISION, RB_SDK_PATCH);
#if defined(CONFIG_RPC_ENABLE) && (CONFIG_RPC_ENABLE == 1)
    rpc_init(NULL);
#endif
    app_rbf_port_config();
    int iRet = pthread_create(&stThread, NULL, cmd_thread, NULL);

    while(1) {
        sleep(1);
    }
    return 0;
}


void exit_rbf(char *argv[], int argc)
{
    exit(0);
}

void test_device(char *argv[], int argc)
{
    if (argc >= 2) {
        if (strcmp(argv[0], "delete") == 0) {
            test_delete(&argv[1], argc-1);
        } else if (strcmp(argv[0], "list") == 0) {
            test_list(NULL, 0);
        }
    } else {
        test_list(NULL, 0);
    }
}