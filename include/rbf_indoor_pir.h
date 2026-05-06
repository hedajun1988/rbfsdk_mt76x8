/**
 * @file rbf_indoor_pir.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Indoor PIR motion sensor API — heartbeat, input events, tamper/fault status, and sensitivity configuration
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef RBF_INDOOR_PIR_H
#define RBF_INDOOR_PIR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief Structure to represent an indoor PIR device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Indoor PIR sensor battery level 0-100 */
    int32_t rssi;   /**< Indoor PIR sensor RSSI */
}rbf_indoor_pir_heartbeat_t;


/**
 * @brief Indoor PIR sensor input event types
 */
typedef enum
{
    RBF_INDOOR_PIR_INPUT_EVT_ALARM = 0,  /**< Indoor PIR sensor detected motion */
}rbf_indoor_pir_input_evt_t;

/**
 * @brief Indoor PIR sensor input status (fault and tamper)
 *
 */
typedef struct
{
    uint8_t fault;   /**< PIR sensor fault: 0 - fault, 1 - normal */
    uint8_t tamper;  /**< PIR sensor tamper status: 0 - tamper normal, 1 - tamper alarm  */
}rbf_indoor_pir_input_status_t;



/**
 * @brief Indoor PIR sensor sensitivity levels
 */
typedef enum
{
    RBF_INDOOR_PIR_SENSITIVEITY_AUTO = 0,   /**< Auto sensitivity */
    RBF_INDOOR_PIR_SENSITIVEITY_LOW,        /**< Low sensitivity */
    RBF_INDOOR_PIR_SENSITIVEITY_MID,        /**< Medium sensitivity */
    RBF_INDOOR_PIR_SENSITIVEITY_HIGH,       /**< High sensitivity */
}rbf_indoor_pir_sensitive_t;

/**
 * @brief Indoor PIR sensor configuration
 */
typedef struct
{
    uint8_t tamper_enable;                      /**< Tamper detection: 0 - disable, 1 - enable */
    rbf_indoor_pir_sensitive_t sensitivity;     /**< PIR sensor sensitivity */
}rbf_indoor_pir_config_t;


/**
 * @brief Callback function to handle indoor PIR device heartbeat events.
 *
 * This function is called whenever an indoor PIR device sends a heartbeat event.
 */
typedef int (*rbf_indoor_pir_heartbeat_callback_t)(uint8_t no, rbf_indoor_pir_heartbeat_t* heartbeat);


/**
 * @brief Callback for indoor PIR input event (motion detected)
 *
 */
typedef int (*rbf_indoor_pir_input_evt_callback_t)(uint8_t no, rbf_indoor_pir_input_evt_t evt);
/**
 * @brief Callback for updating indoor PIR input status information
 *
 */
typedef int (*rbf_indoor_pir_input_status_update_callback_t)(uint8_t no, rbf_indoor_pir_input_status_t* input_status);


/**
 * @brief Indoor PIR sensor callback functions cluster
 *
 */
typedef struct
{
    rbf_indoor_pir_heartbeat_callback_t hb_cb;                                       /**< Heartbeat callback */
    rbf_indoor_pir_input_evt_callback_t input_evt_cb;                               /**< Input event callback */
    rbf_indoor_pir_input_status_update_callback_t input_status_cb;                   /**< Input status update callback */
}rbf_indoor_pir_callbacks_t;



/**
 * @brief Register indoor PIR sensor callback functions cluster
 *
 * @param cbs Indoor PIR sensor callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_indoor_pir_register_callbacks(rbf_indoor_pir_callbacks_t* cbs);


/**
 * @brief Set indoor PIR configuration
 *
 * @param no Indoor PIR registration number
 * @param config Indoor PIR configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_indoor_pir_set(uint8_t no, rbf_indoor_pir_config_t* config);

/**
 * @brief Update indoor PIR configuration immediately via broadcast
 *
 * @param no Indoor PIR registration number
 * @param config Indoor PIR configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_indoor_pir_update(uint8_t no, rbf_indoor_pir_config_t* config);


#ifdef __cplusplus
}
#endif

#endif
