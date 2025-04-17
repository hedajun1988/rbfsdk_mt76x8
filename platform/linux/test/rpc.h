/**
 * @file rpc.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef RPC_H
#define RPC_H

#include <stdint.h>

typedef struct
{
    int (*read)(uint8_t *buf, uint32_t bufsize, uint32_t timeout);
    int (*write)(uint8_t *data, uint32_t dataLen);
}rpc_helper_t;

void rpc_init(rpc_helper_t* helper);
void rpc_module_reset(void);
uint32_t rpc_fw_size_get(void);
uint32_t rpc_subdev_fw_size_get(void);
int rpc_fw_data_get(uint32_t offset, uint32_t size, uint8_t* data);
int rpc_subdev_fw_data_get(uint32_t offset, uint32_t size, uint8_t* data);

#endif