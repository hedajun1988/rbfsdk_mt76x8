/**
 * @file rpc.c
 * @author Jio (hedajun@hzdusun.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/socket.h>  
#include <arpa/inet.h>
#include <netinet/in.h>  
#include <ifaddrs.h>
#include <pthread.h>
#include <net/route.h>
#include <net/if.h>
#include <sys/queue.h>
#include <pthread.h>
#include "rpc.h"


#define RBF_FW_FILE                    "/root/HUB_MODULE_E1_V1.0.1_build24011701.gbl"
#define RBF_SUBDEV_FW_FILE             "/root/RBSS-MC1-868_V1.0.3_1.1.2_build25032801_LZMA_OTA.gbl"

char hub_fw_file[100];
char subdev_fw_file[100];


int rpc_get_config(const char* searchKey, char* path)
{
    FILE *file;
    char line[100];
    char key[100];
    char value[100];
    
    // 打开配置文件
    file = fopen("/root/agent.conf", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open /root/agent.conf\n");
        return 1;
    }
    
    // 读取配置文件中的每一行
    while (fgets(line, sizeof(line), file) != NULL) {
        // 分离键和值
        sscanf(line, "%[^=]=%s", key, value);
        
        // 检查是否找到指定的键
        if (strcmp(key, searchKey) == 0) {
            printf("%s is: %s\n", key, value);
            strcpy(path, value);
            break;
        }
    }
    
    // 关闭文件
    fclose(file);

    return 0;
}

void rpc_init(rpc_helper_t* helper)
{
    (void)helper;
    if (rpc_get_config("hub_fw", hub_fw_file) != 0) {
        strcpy(hub_fw_file, RBF_FW_FILE);
    } 

    if (rpc_get_config("subdev_fw", subdev_fw_file) != 0) {
        strcpy(subdev_fw_file, RBF_SUBDEV_FW_FILE);
    } 

    return;
}



void rpc_module_reset(void)
{
    system("echo 1 > /sys/class/gpio/gpio22/value");
    usleep(100*1000);
    system("echo 0 > /sys/class/gpio/gpio22/value");
}

int rpc_load_hub_firmware(char *filename)
{
    FILE *fp = fopen(filename, "r+");
    int fw_size = 0;

    if (fp) {
        fseek(fp, 0L, SEEK_END);
        fw_size = ftell(fp);
        printf("fw size: %d\n", fw_size);
        fclose(fp);
    }

    return fw_size;
}


uint32_t rpc_fw_size_get(void)
{
    uint32_t fw_size = rpc_load_hub_firmware(hub_fw_file);
    printf("rpc hub get fw size [%u]\n", fw_size);
    return fw_size;
}

uint32_t rpc_subdev_fw_size_get(void)
{
    uint32_t fw_size = rpc_load_hub_firmware(subdev_fw_file);
    printf("rpc subdev get subdev fw size [%u]\n", fw_size);
    return fw_size;
}

int _rpc_fw_data_get_from_file(char *filename, uint32_t offset, uint32_t size, uint8_t* data)
{
    FILE *fp = fopen(filename, "r+");
    int read_size = 0;

    if (fp) {
        fseek(fp, offset, SEEK_SET);
        read_size = fread((char *)data, 1, size, fp);
        fclose(fp);
    }

    return (read_size == size) ? 0 : -1;
}

int rpc_fw_data_get(uint32_t offset, uint32_t size, uint8_t* data)
{
    printf("request rbf hub fw data offset %u size %u\n", offset, size);
    return _rpc_fw_data_get_from_file(hub_fw_file, offset, size, data);
}



int rpc_subdev_fw_data_get(uint32_t offset, uint32_t size, uint8_t* data)
{
    printf("request rbf subdev fw data offset %u size %u\n", offset, size);
    return _rpc_fw_data_get_from_file(subdev_fw_file, offset, size, data);
}


