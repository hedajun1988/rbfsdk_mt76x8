
#ifndef RBF_TEST_H
#define RBF_TEST_H


void test_enroll(char *argv[], int argc);
void test_stop_enroll(char *argv[], int argc);
void test_findme_start(char *argv[], int argc);
void test_findme_stop(char *argv[], int argc);
void test_rssi_start(char *argv[], int argc);
void test_rssi_stop(char *argv[], int argc);
void test_ledset(char *argv[], int argc);
void test_delete(char *argv[], int argc);
void test_list(char *argv[], int argc);
void test_outdoor_sounder(char *argv[], int argc);
void test_indoor_siren(char *argv[], int argc);
void test_pir(char *argv[], int argc);
void test_temphumi(char *argv[], int argc);
void test_sethub(char *argv[], int argc);
void test_setarming(char *argv[], int argc);
void test_keypad(char *argv[], int argc);
void test_relay(char *argv[], int argc);
void test_wall_switch(char *argv[], int argc);
void test_ota(char *argv[], int argc);
void test_subdev_ota(char *argv[], int argc);
void test_hub(char *argv[], int argc);
void test_smartplug(char *argv[], int argc);
void delete(char *argv[], int argc);
void init_rbf(char *argv[], int argc);


int test_rbf_init(void);

#endif