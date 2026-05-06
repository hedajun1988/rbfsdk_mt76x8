/**
 * @file rbf_subdev_ota.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Sub-device OTA (Over-The-Air) firmware upgrade API — events, error codes, status, and batch upgrade control
 * @version 0.1
 * @date 2025-04-01
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_SUBDEV_OTA_H
#define RBF_SUBDEV_OTA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Sub-device OTA upgrade events reported during the upgrade process
 *
 */
typedef enum
{
    RBF_SUBDEV_OTA_EVT_UPGRADE_COMPLETE = 0,                   /**< Upgrade completed successfully */
    RBF_SUBDEV_OTA_EVT_UPGRADE_FAIL,                           /**< Upgrade failed */
    RBF_SUBDEV_OTA_EVT_UPGRADE_REQUEST_TIMEOUT,                /**< Upgrade request timeout */
    RBF_SUBDEV_OTA_EVT_PAGE_TRANS_FAILED,                      /**< Upgrade page transmission failed */
    RBF_SUBDEV_OTA_EVT_PAGE_TRANS_SUCESS,                      /**< Upgrade page transmission succeeded */
    RBF_SUBDEV_OTA_EVT_TRANS_SUCESS,                           /**< Upgrade transmission succeeded */
}RBF_subdev_ota_evt_t;


/**
 * @brief Sub-device OTA error codes describing the cause of upgrade failures
 */
typedef enum
{
    RBF_SUBDEV_OTA_ERR_CODE_UNKNOWN = 0,                     /**< Unknown error */
    RBF_SUBDEV_OTA_ERR_CODE_HANDSHAKE_FAIL,                  /**< Handshake failure */
    RBF_SUBDEV_OTA_ERR_CODE_TRANS_LOSS_OR_CHECKSUM_ERR,      /**< Data transmission loss or checksum error */
    RBF_SUBDEV_OTA_ERR_CODE_TRANS_FAILED_TO_MANY_TIMES,      /**< Data transmission failed too many times */
    RBF_SUBDEV_OTA_ERR_CODE_CHECKSUM_TIMEOUT,                /**< Checksum timeout */
    RBF_SUBDEV_OTA_ERR_CODE_SIGNATURE_VERIFYCATION_FAILED,   /**< Signature verification failed */
    RBF_SUBDEV_OTA_ERR_CODE_ABNORMALLY_EXITED,               /**< Hub OTA process exited abnormally */
    RBF_SUBDEV_OTA_ERR_CODE_SUBDEV_NOT_SUPPORTED,            /**< Sub-device does not support OTA */
    RBF_SUBDEV_OTA_ERR_CODE_HUB_RECEIVE_FILE_TIMEOUT,        /**< Hub did not receive file for over 20 seconds */
}RBF_subdev_ota_err_code_t;

/**
 * @brief Sub-device OTA upgrade progress status
 *
 */
typedef struct
{
    bool upgrading;     /**< Whether an upgrade is currently in progress */
    uint8_t percent;    /**< Upgrade progress percentage: 0-100 */
}RBF_subdev_ota_status_t;

/**
 * @brief Response entry for a sub-device that failed to upgrade (returned in batch upgrade failure events)
 */
typedef struct
{
    uint8_t devno;                          /**< Sub-device registration number */
    RBF_subdev_ota_err_code_t errorcode;    /**< Error code for the failure */
}RBF_subdev_ota_faild_response_t;

/**
 * @brief Sub-device OTA event callback functions cluster
 */
typedef struct
{
    /**
     * @brief Sub-device OTA service request to fetch upgrade firmware data
     * @param offset Firmware offset address
     * @param size Requested data length
     * @param data Output buffer for the requested firmware data
     * @return int Whether the firmware data was successfully obtained: 0-success, other values-failure
     */
    int (*rbf_subdev_ota_request_upgrade_data_handle)(unsigned int offset, unsigned int size, unsigned char* data);

    /**
     * @brief Sub-device OTA event reporting callback
     * @param evt Sub-device OTA event
     * @param responses Array of failure responses for sub-devices that failed to upgrade.
     * Sub-device upgrades allow simultaneous upgrades of multiple devices, which may result
     * in failures for one or more devices among them.
     * @param response_count Number of entries in the responses array
     * @param trans_byte Number of bytes transmitted in this event
     * @return int Result of processing the event: 0-success, other values-failure
     */
    int (*rbf_subdev_ota_evt_handle)(RBF_subdev_ota_evt_t evt, RBF_subdev_ota_faild_response_t* responses, uint8_t response_count, int trans_byte);
}RBF_subdev_ota_evt_callbacks_t;


/**
 * @brief Register sub-device OTA callback function cluster
 *
 * @param cbs  Sub-device OTA callback function cluster
 * @return int 0-success, -1-failure
 */
int rbf_subdev_ota_register_evt_callback(RBF_subdev_ota_evt_callbacks_t* cbs);

/**
 * @brief Start sub-device OTA upgrade for a batch of devices
 *
 * @param cat The sub-device category
 * @param no_list The list of sub-device registration numbers
 * @param count The count of no_list, supports upgrading up to 12 sub-devices simultaneously.
 * @param fw_size Firmware size in bytes
 * @return int 0-success, -1-failure
 */
int rbf_subdev_ota_start(uint8_t cat, uint8_t* no_list, uint8_t count, uint32_t fw_size);


#ifdef __cplusplus
}
#endif

#endif
