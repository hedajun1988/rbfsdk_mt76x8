/**
 * @file rbf_wall_switch.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Wall switch (strong relay) device API — heartbeat with electrical measurements, output status, configuration, and on/off control
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_WALL_SWITCH_H
#define RBF_WALL_SWITCH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief Wall switch heartbeat data reported periodically with electrical measurements
 */
typedef struct
{
    uint8_t onoff;          /**< Wall switch output status: 0-off, 1-on */
    uint8_t over_volt;      /**< Over-voltage alarm: 0-normal, 1-overvoltage */
    uint8_t over_curr;      /**< Over-current alarm: 0-normal, 1-overcurrent */
    uint8_t under_volt;     /**< Under-voltage alarm: 0-normal, 1-undervoltage */
    uint8_t over_load;      /**< Overload alarm: 0-normal, 1-overload */
    uint32_t inst_volt;     /**< Instantaneous voltage */
    uint32_t inst_curr;     /**< Instantaneous current */
    uint32_t inst_power;    /**< Instantaneous power */
    int32_t rssi;           /**< Wall switch RSSI */
}rbf_wall_switch_heartbeat_t;


/**
 * @brief Wall switch output status reported on state change
 *
 */
typedef struct
{
    uint8_t onoff;          /**< Wall switch output status: 0-off, 1-on */
    uint8_t over_volt;      /**< Over-voltage alarm: 0-normal, 1-overvoltage */
    uint8_t over_curr;      /**< Over-current alarm: 0-normal, 1-overcurrent */
    uint8_t under_volt;     /**< Under-voltage alarm: 0-normal, 1-undervoltage */
    uint8_t over_load;      /**< Overload alarm: 0-normal, 1-overload */
}rbf_wall_switch_output_status_t;

/**
 * @brief Wall switch control action
 */
typedef enum
{
    RBF_WALL_SWITCH_ACTION_NONE = 0,    /**< No action */
    RBF_WALL_SWITCH_ACTION_ON,          /**< Turn wall switch on */
    RBF_WALL_SWITCH_ACTION_OFF,         /**< Turn wall switch off */
    RBF_WALL_SWITCH_ACTION_TOOGLE,      /**< Toggle wall switch state */
}rbf_wall_switch_action_t;


/**
 * @brief Wall switch control command
 */
typedef struct
{
    rbf_wall_switch_action_t action;    /**< Control action to execute */
}rbf_wall_switch_ctrl_t;

/**
 * @brief Wall switch power-on default state
 */
typedef enum
{
    RBF_WALL_SWITCH_DEFAULT_ON = 0,     /**< Default on after power-up */
    RBF_WALL_SWITCH_DEFAULT_OFF,        /**< Default off after power-up */
    RBF_WALL_SWITCH_DEFAULT_MEMORY,     /**< Restore last state after power-up */
}rbf_wall_switch_default_state_t;

/**
 * @brief Wall switch state lock — prevents local control from changing output state
 */
typedef enum
{
    RBF_WALL_SWITCH_STATE_LOCK_DISABLE = 0, /**< State lock disabled */
    RBF_WALL_SWITCH_STATE_LOCK_OFF,         /**< Lock output off regardless of local action */
    RBF_WALL_SWITCH_STATE_LOCK_ON,          /**< Lock output on regardless of local action */
}rbf_wall_switch_state_lock_t;


/**
 * @brief Wall switch configuration parameters
 */
typedef struct
{
    rbf_wall_switch_default_state_t default_state;  /**< Default output state after power-up */
    uint8_t pulse_enable;                            /**< Pulse mode enable: 0-disable, 1-enable */
    rbf_wall_switch_state_lock_t state_lock;         /**< Output state lock setting */
    uint8_t time_of_pulse_in_seconds;                /**< Pulse duration in seconds (when pulse mode is enabled) */
}rbf_wall_switch_config_t;


/**
 * @brief Wall switch control result error codes
 */
typedef enum
{
    RBF_WALL_SWITCH_CTRL_SUCESS = 0,    /**< Control operation succeeded */
    RBF_WALL_SWITCH_CTRL_FAIL,          /**< Control operation failed */
    RBF_WALL_SWITCH_CTRL_TIMEOUT,       /**< Control operation timed out */
}rbf_wall_switch_ctrl_err_code_t;

/**
 * @brief Wall switch control result returned after a control command
 */
typedef struct
{
    rbf_wall_switch_ctrl_err_code_t err_code;   /**< Error code: 0-success, other values-failure */
    uint8_t onoff;                              /**< Output status: 0-off, 1-on, 0xFF-invalid */
}rbf_wall_switch_ctrl_result_t;

/**
 * @brief Wall switch heartbeat callback handler
 * @param no Device registration number
 * @param heartbeat Heartbeat information
 */
typedef int (*rbf_wall_switch_heartbeat_callback_t)(uint8_t no, rbf_wall_switch_heartbeat_t* heartbeat);

/**
 * @brief Callback for wall switch output status changed
 *
 */
typedef int (*rbf_wall_switch_output_status_callback_t)(uint8_t no, rbf_wall_switch_output_status_t* status);

/**
 * @brief Wall switch callback functions cluster
 *
 */
typedef struct
{
    rbf_wall_switch_heartbeat_callback_t hb_cb;                     /**< Heartbeat callback */
    rbf_wall_switch_output_status_callback_t output_status_cb;      /**< Output status change callback */
}rbf_wall_switch_callbacks_t;


/**
 * @brief Register wall switch callback functions cluster
 *
 * @param cbs Wall switch callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_wall_switch_register_callbacks(rbf_wall_switch_callbacks_t* cbs);


/**
 * @brief Set wall switch configuration — takes effect on next sub-device wake-up via synchronous broadcast
 *
 * @param no Wall switch registration number
 * @param config Wall switch configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_wall_switch_set(uint8_t no, rbf_wall_switch_config_t* config);

/**
 * @brief Update wall switch configuration immediately via broadcast
 *
 * @param no Wall switch registration number
 * @param config Wall switch configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_wall_switch_update(uint8_t no, rbf_wall_switch_config_t* config);

/**
 * @brief Control wall switch on/off/toggle with blocking response (up to 6s timeout)
 *
 * @param no Wall switch registration number
 * @param ctrl Wall switch control action
 * @param result Control result output (error code and final output state)
 * @return int 0: successful, -1: failed
 */
int rbf_wall_switch_ctrl(uint8_t no, rbf_wall_switch_ctrl_t* ctrl, rbf_wall_switch_ctrl_result_t* result);

#ifdef __cplusplus
}
#endif

#endif
