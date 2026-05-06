/**
 * @file rbf_outdoor_pir.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Outdoor PIR motion sensor API — heartbeat, input events, tamper/fault status, and sensitivity configuration
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef RBF_OUTDOOR_PIR_H
#define RBF_OUTDOOR_PIR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief Structure to represent an outdoor PIR device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Outdoor PIR sensor battery level 0-100 */
    int32_t rssi;   /**< Outdoor PIR sensor RSSI */
}rbf_outdoor_pir_heartbeat_t;


/**
 * @brief Outdoor PIR sensor input event types
 */
typedef enum
{
    RBF_OUTDOOR_PIR_INPUT_EVT_ALARM = 0,  /**< Outdoor PIR sensor detected motion */
}rbf_outdoor_pir_input_evt_t;

/**
 * @brief Outdoor PIR sensor input status (fault and tamper)
 *
 */
typedef struct
{
    uint8_t fault;   /**< PIR sensor fault: 0 - fault, 1 - normal */
    uint8_t tamper;  /**< PIR sensor tamper status: 0 - tamper normal, 1 - tamper alarm  */
}rbf_outdoor_pir_input_status_t;



/**
 * @brief Outdoor PIR sensor sensitivity levels
 */
typedef enum
{
    RBF_OUTDOOR_PIR_SENSITIVEITY_AUTO = 0,  /**< Auto sensitivity */
    RBF_OUTDOOR_PIR_SENSITIVEITY_LOW,       /**< Low sensitivity */
    RBF_OUTDOOR_PIR_SENSITIVEITY_MID,       /**< Medium sensitivity */
    RBF_OUTDOOR_PIR_SENSITIVEITY_HIGH,      /**< High sensitivity */
}rbf_outdoor_pir_sensitive_t;

/**
 * @brief Outdoor PIR sensor configuration
 */
typedef struct
{
    uint8_t tamper_enable;                      /**< Tamper detection: 0 - disable, 1 - enable */
    rbf_outdoor_pir_sensitive_t sensitivity;     /**< PIR sensor sensitivity */
}rbf_outdoor_pir_config_t;


/**
 * @brief Callback function to handle outdoor PIR device heartbeat events.
 *
 * This function is called whenever an outdoor PIR device sends a heartbeat event.
 */
typedef int (*rbf_outdoor_pir_heartbeat_callback_t)(uint8_t no, rbf_outdoor_pir_heartbeat_t* heartbeat);


/**
 * @brief Callback for outdoor PIR input event (motion detected)
 *
 */
typedef int (*rbf_outdoor_pir_input_evt_callback_t)(uint8_t no, rbf_outdoor_pir_input_evt_t evt);
/**
 * @brief Callback for updating outdoor PIR input status information
 *
 */
typedef int (*rbf_outdoor_pir_input_status_update_callback_t)(uint8_t no, rbf_outdoor_pir_input_status_t* input_status);


/**
 * @brief Outdoor PIR sensor callback functions cluster
 *
 */
typedef struct
{
    rbf_outdoor_pir_heartbeat_callback_t hb_cb;                                      /**< Heartbeat callback */
    rbf_outdoor_pir_input_evt_callback_t input_evt_cb;                              /**< Input event callback */
    rbf_outdoor_pir_input_status_update_callback_t input_status_cb;                  /**< Input status update callback */
}rbf_outdoor_pir_callbacks_t;



/**
 * @brief Register outdoor PIR sensor callback functions cluster
 *
 * @param cbs Outdoor PIR sensor callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_outdoor_pir_register_callbacks(rbf_outdoor_pir_callbacks_t* cbs);


/**
 * @brief Set outdoor PIR configuration
 *
 * @param no Outdoor PIR registration number
 * @param config Outdoor PIR configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_outdoor_pir_set(uint8_t no, rbf_outdoor_pir_config_t* config);

/**
 * @brief Update outdoor PIR configuration immediately via broadcast
 *
 * @param no Outdoor PIR registration number
 * @param config Outdoor PIR configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_outdoor_pir_update(uint8_t no, rbf_outdoor_pir_config_t* config);


#ifdef __cplusplus
}
#endif

#endif
