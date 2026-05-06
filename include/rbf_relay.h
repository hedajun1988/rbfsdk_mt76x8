/**
 * @file rbf_relay.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Weak relay device API — heartbeat, output status, configuration, and on/off control
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_RELAY_H
#define RBF_RELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Relay heartbeat data reported periodically by the device
 */
typedef struct
{
    uint8_t onoff;  /**< Relay output status: 0-off, 1-on */
    int32_t rssi;   /**< Relay RSSI */
}rbf_relay_heartbeat_t;

/**
 * @brief Relay output status reported on state change
 *
 */
typedef struct
{
    uint8_t onoff;  /**< Relay output status: 0-off, 1-on */
}rbf_relay_output_status_t;

/**
 * @brief Relay heartbeat callback handler
 * @param no Device registration number
 * @param heartbeat Heartbeat information
 */
typedef int (*rbf_relay_heartbeat_callback_t)(uint8_t no, rbf_relay_heartbeat_t* heartbeat);


/**
 * @brief Callback for relay output status changed
 *
 */
typedef int (*rbf_relay_output_status_callback_t)(uint8_t no, rbf_relay_output_status_t* status);


/**
 * @brief Relay callback functions cluster
 *
 */
typedef struct
{
    rbf_relay_heartbeat_callback_t hb_cb;               /**< Heartbeat callback */
    rbf_relay_output_status_callback_t output_status_cb; /**< Output status change callback */
}rbf_relay_callbacks_t;


/**
 * @brief Relay control action
 */
typedef enum
{
    RBF_RELAY_ACTION_NONE = 0,  /**< No action */
    RBF_RELAY_ACTION_ON,        /**< Turn relay on */
    RBF_RELAY_ACTION_OFF,       /**< Turn relay off */
    RBF_RELAY_ACTION_TOOGLE,    /**< Toggle relay state */
}rbf_relay_action_t;


/**
 * @brief Relay control command
 */
typedef struct
{
    rbf_relay_action_t action;  /**< Control action to execute */
}rbf_relay_ctrl_t;


/**
 * @brief Relay power-on default state
 */
typedef enum
{
    RBF_RELAY_DEFAULT_ON = 0,   /**< Default on after power-up */
    RBF_RELAY_DEFAULT_OFF,      /**< Default off after power-up */
    RBF_RELAY_DEFAULT_MEMORY,   /**< Restore last state after power-up */
}rbf_relay_default_state_t;

/**
 * @brief Relay state lock — prevents local control from changing output state
 */
typedef enum
{
    RBF_RELAY_STATE_LOCK_DISABLE = 0,   /**< State lock disabled */
    RBF_RELAY_STATE_LOCK_OFF,           /**< Lock output off regardless of local action */
    RBF_RELAY_STATE_LOCK_ON,            /**< Lock output on regardless of local action */
}rbf_relay_state_lock_t;


/**
 * @brief Relay configuration parameters
 */
typedef struct
{
    rbf_relay_default_state_t default_state;    /**< Default output state after power-up */
    uint8_t pulse_enable;                       /**< Pulse mode enable: 0-disable, 1-enable */
    rbf_relay_state_lock_t state_lock;          /**< Output state lock setting */
    uint8_t time_of_pulse_in_seconds;           /**< Pulse duration in seconds (when pulse mode is enabled) */
}rbf_relay_config_t;


/**
 * @brief Relay control result error codes
 */
typedef enum
{
    RBF_RELAY_CTRL_SUCESS = 0,  /**< Control operation succeeded */
    RBF_RELAY_CTRL_FAIL,        /**< Control operation failed */
    RBF_RELAY_CTRL_TIMEOUT,     /**< Control operation timed out */
}rbf_relay_ctrl_err_code_t;

/**
 * @brief Relay control result returned after a control command
 */
typedef struct
{
    rbf_relay_ctrl_err_code_t err_code; /**< Error code: 0-success, other values-failure */
    uint8_t onoff;                      /**< Output status: 0-off, 1-on, 0xFF-invalid */
}rbf_relay_ctrl_result_t;

/**
 * @brief Register relay callback functions cluster
 *
 * @param cbs Relay callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_relay_register_callbacks(rbf_relay_callbacks_t* cbs);


/**
 * @brief Set relay configuration — takes effect on next sub-device wake-up via synchronous broadcast
 *
 * @param no Relay registration number
 * @param config Relay configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_relay_set(uint8_t no, rbf_relay_config_t* config);

/**
 * @brief Update relay configuration immediately via broadcast
 *
 * @param no Relay registration number
 * @param config Relay configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_relay_update(uint8_t no, rbf_relay_config_t* config);

/**
 * @brief Control relay on/off/toggle with blocking response (up to 6s timeout)
 *
 * @param no Relay registration number
 * @param ctrl Relay control action
 * @param result Control result output (error code and final output state)
 * @return int 0: successful, -1: failed
 */
int rbf_relay_ctrl(uint8_t no, rbf_relay_ctrl_t* ctrl, rbf_relay_ctrl_result_t* result);


#ifdef __cplusplus
}
#endif

#endif
