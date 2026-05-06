/**
 * @file rbf_ota.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Hub OTA (Over-The-Air) firmware upgrade API — events, status, and upgrade control
 * @version 0.1
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_OTA_H
#define RBF_OTA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief OTA upgrade events reported during the upgrade process
 *
 */
typedef enum
{
    RBF_OTA_EVT_ENTER_BOOTLOADER_SUCESS = 0,        /**< Entering bootloader successfully */
    RBF_OTA_EVT_ENTER_BOOTLOADER_FAIL,              /**< Failed to enter bootloader */
    RBF_OTA_EVT_START_SUCCESS,                      /**< Upgrade started successfully */
    RBF_OTA_EVT_START_FAIL,                         /**< Failed to start the upgrade */
    RBF_OTA_EVT_UPGRADE_PROGRESS_UPDATE,            /**< Upgrade progress update */
    RBF_OTA_EVT_UPGRADE_COMPLETE,                   /**< Upgrade completed successfully */
    RBF_OTA_EVT_UPGRADE_FAIL,                       /**< Upgrade failed */
}RBF_ota_evt_t;


/**
 * @brief OTA upgrade progress status
 *
 */
typedef struct
{
    bool upgrading;     /**< Whether an upgrade is currently in progress */
    uint8_t percent;    /**< Upgrade progress percentage: 0-100 */
}RBF_ota_status_t;


/**
 * @brief OTA event callback functions cluster
 */
typedef struct
{
    /**
     * @brief OTA service request to fetch upgrade firmware data
     * @param offset Firmware offset address
     * @param size Requested data length
     * @param data Output buffer for the requested firmware data
     * @return int Whether the firmware data was successfully obtained: 0-success, other values-failure
     */
    int (*rbf_ota_request_upgrade_data_handle)(unsigned int offset, unsigned int size, unsigned char* data);

    /**
     * @brief OTA event reporting callback
     * @param evt OTA event
     * @param status OTA status information (valid for progress update events)
     * @return int Result of processing the event: 0-success, other values-failure
     */
    int (*rbf_ota_evt_handle)(RBF_ota_evt_t evt, RBF_ota_status_t* status);
}RBF_ota_evt_callbacks_t;


/**
 * @brief Register OTA callback function cluster
 *
 * @param cbs  OTA callback function cluster
 * @return int 0-success, -1-failure
 */
int rbf_ota_register_evt_callback(RBF_ota_evt_callbacks_t* cbs);

/**
 * @brief Get current OTA status information
 *
 * @param status Output OTA status information
 * @return int 0-success, -1-failure
 */
int rbf_ota_status_get(RBF_ota_status_t* status);

/**
 * @brief Start OTA upgrade for the hub
 *
 * @param fw_size Total firmware size in bytes
 * @return int 0-success, -1-failure
 */
int rbf_ota_start(uint32_t fw_size);



#ifdef __cplusplus
}
#endif


#endif
