/**
 * @file rbf_smartplug.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Smart plug device API — heartbeat with electrical measurements, output status, configuration, and on/off control
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_SMARTPLUG_H
#define RBF_SMARTPLUG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Smart plug heartbeat data reported periodically with electrical measurements
 */
typedef struct
{
    uint8_t onoff;          /**< Smart plug output status: 0-off, 1-on */
    uint8_t over_volt;      /**< Over-voltage alarm: 0-normal, 1-overvoltage */
    uint8_t over_curr;      /**< Over-current alarm: 0-normal, 1-overcurrent */
    uint8_t under_volt;     /**< Under-voltage alarm: 0-normal, 1-undervoltage */
    uint8_t over_load;      /**< Overload alarm: 0-normal, 1-overload */
    uint8_t lock;           /**< Child lock status: 0-unlocked, 1-locked */
    uint32_t inst_volt;     /**< Instantaneous voltage */
    uint32_t inst_curr;     /**< Instantaneous current */
    uint32_t inst_power;    /**< Instantaneous power */
    uint32_t run_time;      /**< Run time in seconds */
    uint32_t cumu_power;    /**< Cumulative power (0.1 KWh) */
    int32_t rssi;           /**< Smart plug RSSI */
}rbf_smartplug_heartbeat_t;



/**
 * @brief Smart plug output status reported on state change
 *
 */
typedef struct
{
    uint8_t onoff;          /**< Smart plug output status: 0-off, 1-on */
    uint8_t over_volt;      /**< Over-voltage alarm: 0-normal, 1-overvoltage */
    uint8_t over_curr;      /**< Over-current alarm: 0-normal, 1-overcurrent */
    uint8_t under_volt;     /**< Under-voltage alarm: 0-normal, 1-undervoltage */
    uint8_t over_load;      /**< Overload alarm: 0-normal, 1-overload */
    uint8_t lock;           /**< Child lock status: 0-unlocked, 1-locked */
}rbf_smartplug_output_status_t;



/**
 * @brief Smart plug heartbeat callback handler
 * @param no Device registration number
 * @param heartbeat Heartbeat information
 */
typedef int (*rbf_smartplug_heartbeat_callback_t)(uint8_t no, rbf_smartplug_heartbeat_t* heartbeat);

/**
 * @brief Callback for smart plug output status changed
 *
 */
typedef int (*rbf_smartplug_output_status_callback_t)(uint8_t no, rbf_smartplug_output_status_t* status);


/**
 * @brief Smart plug callback functions cluster
 *
 */
typedef struct
{
    rbf_smartplug_heartbeat_callback_t hb_cb;                   /**< Heartbeat callback */
    rbf_smartplug_output_status_callback_t output_status_cb;    /**< Output status change callback */
}rbf_smartplug_callbacks_t;


/**
 * @brief Smart plug control action
 */
typedef enum
{
    RBF_SMARTPLUG_ACTION_NONE = 0,  /**< No action */
    RBF_SMARTPLUG_ACTION_ON,        /**< Turn smart plug on */
    RBF_SMARTPLUG_ACTION_OFF,       /**< Turn smart plug off */
    RBF_SMARTPLUG_ACTION_TOOGLE,    /**< Toggle smart plug state */
}rbf_smartplug_action_t;


/**
 * @brief Smart plug control command
 */
typedef struct
{
    rbf_smartplug_action_t action;  /**< Control action to execute */
    uint8_t lock;                   /**< Child lock: 0-unlocked, 1-locked (disables local button control) */
}rbf_smartplug_ctrl_t;

/**
 * @brief Smart plug power-on default state
 */
typedef enum
{
    RBF_SMARTPLUG_DEFAULT_ON = 0,   /**< Default on after power-up */
    RBF_SMARTPLUG_DEFAULT_OFF,      /**< Default off after power-up */
    RBF_SMARTPLUG_DEFAULT_MEMORY,   /**< Restore last state after power-up */
}rbf_smartplug_default_state_t;

/**
 * @brief Smart plug state lock — prevents local control from changing output state
 */
typedef enum
{
    RBF_SMARTPLUG_STATE_LOCK_DISABLE = 0,   /**< State lock disabled */
    RBF_SMARTPLUG_STATE_LOCK_OFF,           /**< Lock output off regardless of local action */
    RBF_SMARTPLUG_STATE_LOCK_ON,            /**< Lock output on regardless of local action */
}rbf_smartplug_state_lock_t;

/**
 * @brief Smart plug configuration parameters
 */
typedef struct
{
    rbf_smartplug_default_state_t default_state;    /**< Default output state after power-up */
    rbf_smartplug_state_lock_t state_lock;          /**< Output state lock setting */
}rbf_smartplug_config_t;


/**
 * @brief Smart plug control result error codes
 */
typedef enum
{
    RBF_SMARTPLUG_CTRL_SUCESS = 0,  /**< Control operation succeeded */
    RBF_SMARTPLUG_CTRL_FAIL,        /**< Control operation failed */
    RBF_SMARTPLUG_CTRL_TIMEOUT,     /**< Control operation timed out */
}rbf_smartplug_ctrl_err_code_t;

/**
 * @brief Smart plug control result returned after a control command
 */
typedef struct
{
    rbf_smartplug_ctrl_err_code_t err_code; /**< Error code: 0-success, other values-failure */
    uint8_t onoff;                          /**< Output status: 0-off, 1-on, 0xFF-invalid */
}rbf_smartplug_ctrl_result_t;

/**
 * @brief Register smart plug callback functions cluster
 *
 * @param cbs Smart plug callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_smartplug_register_callbacks(rbf_smartplug_callbacks_t* cbs);


/**
 * @brief Set smart plug configuration — takes effect on next sub-device wake-up via synchronous broadcast
 *
 * @param no Smart plug registration number
 * @param config Smart plug configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_smartplug_set(uint8_t no, rbf_smartplug_config_t* config);

/**
 * @brief Update smart plug configuration immediately via broadcast
 *
 * @param no Smart plug registration number
 * @param config Smart plug configuration parameters
 * @return int 0: successful, -1: failed
 */
int rbf_smartplug_update(uint8_t no, rbf_smartplug_config_t* config);

/**
 * @brief Control smart plug on/off/toggle with blocking response (up to 6s timeout)
 *
 * @param no Smart plug registration number
 * @param ctrl Smart plug control action and child lock setting
 * @param reslut Control result output (error code and final output state)
 * @return int 0: successful, -1: failed
 */
int rbf_smartplug_ctrl(uint8_t no, rbf_smartplug_ctrl_t* ctrl, rbf_smartplug_ctrl_result_t* reslut);


#ifdef __cplusplus
}
#endif

#endif
