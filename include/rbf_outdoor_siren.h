/**
 * @file rbf_outdoor_siren.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Outdoor siren device API — heartbeat, input status (power/solar/battery/tamper), volume control, alarm action/mode, and broadcast control
 * @version 0.1
 * @date 2025-10-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_OUTDOOR_SIREN_H
#define RBF_OUTDOOR_SIREN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Outdoor siren volume level
 *
 */
typedef enum
{
    RBF_OUTDOOR_SIREN_VOLUME_LOW = 0,
    RBF_OUTDOOR_SIREN_VOLUME_MID,
    RBF_OUTDOOR_SIREN_VOLUME_HIGH,
} rbf_outdoor_siren_volume_t;


/**
 * @brief Structure to represent an outdoor siren device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Outdoor siren battery level 0-100 */
    int32_t rssi;   /**< Outdoor siren RSSI */
}rbf_outdoor_siren_heartbeat_t;


/**
 * @brief Outdoor siren status information (power, solar, battery, tamper)
 *
 */
typedef struct
{
    uint8_t power_supply_status; /**< External power supply: 0 - disconnected, 1 - connected */
    uint8_t solar_panels_fault;  /**< Solar panel fault: 0 - No fault, 1 - Fault */
    uint8_t battery_fault;       /**< Battery status: 0 - Battery connected, 1 - Battery not connected */
    uint8_t charge_status;       /**< Solar charging status: 0 - Not charging, 1 - Charging */
    uint8_t tamper;              /**< Tamper status: 0 - Tamper normal, 1 - Tamper alarm */
}rbf_outdoor_siren_input_status_t;

/**
 * @brief Outdoor siren control action — one-shot alarm behaviors
 */
typedef enum
{
    RBF_OUTDOOR_SIREN_CTRL_DISABLED = 0,    /**< No action */
    RBF_OUTDOOR_SIREN_LIGHT_ALARM_ONCE,     /**< Flash light alarm once */
    RBF_OUTDOOR_SIREN_SOUND_ALARM_ONCE,     /**< Sound alarm once */
    RBF_OUTDOOR_SIREN_MIXED_ALARM_ONCE,     /**< Mixed light+sound alarm once */
    RBF_OUTDOOR_SIREN_LIGHT_ALARM_TWICE,    /**< Flash light alarm twice */
    RBF_OUTDOOR_SIREN_SOUND_ALARM_TWICE,    /**< Sound alarm twice */
    RBF_OUTDOOR_SIREN_MIXED_ALARM_TWICE,    /**< Mixed light+sound alarm twice */
    RBF_OUTDOOR_SIREN_ALARM_COUNT_DOWN,     /**< Countdown alarm */
} rbf_outdoor_siren_ctrl_action_t;


/**
 * @brief Outdoor siren control mode — persistent alarm states
 */
typedef enum
{
    RBF_OUTDOOR_SIREN_MODE_DISABLED = 0,            /**< Alarm mode disabled */
    RBF_OUTDOOR_SIREN_MODE_INVASION_LIGHT_ALARM,    /**< Invasion light alarm mode */
    RBF_OUTDOOR_SIREN_MODE_INVASION_SOUND_ALARM,    /**< Invasion sound alarm mode */
    RBF_OUTDOOR_SIREN_MODE_INVASION_MIXED_ALARM,    /**< Invasion mixed alarm mode */
    RBF_OUTDOOR_SIREN_MODE_FIRE_LIGHT_ALARM,        /**< Fire light alarm mode */
    RBF_OUTDOOR_SIREN_MODE_FIRE_SOUND_ALARM,        /**< Fire sound alarm mode */
    RBF_OUTDOOR_SIREN_MODE_FIRE_MIXED_ALARM,        /**< Fire mixed alarm mode */
    RBF_OUTDOOR_SIREN_MODE_EMERGENCY_LIGHT_ALARM,   /**< Emergency light alarm mode */
    RBF_OUTDOOR_SIREN_MODE_EMERGENCY_SOUND_ALARM,   /**< Emergency sound alarm mode */
    RBF_OUTDOOR_SIREN_MODE_EMERGENCY_MIXED_ALARM,   /**< Emergency mixed alarm mode */
    RBF_OUTDOOR_SIREN_MODE_MEDICAL_LIGHT_ALARM,     /**< Medical light alarm mode */
    RBF_OUTDOOR_SIREN_MODE_MEDICAL_SOUND_ALARM,     /**< Medical sound alarm mode */
    RBF_OUTDOOR_SIREN_MODE_MEDICAL_MIXED_ALARM,     /**< Medical mixed alarm mode */
} rbf_outdoor_siren_ctrl_mode_t;




/**
 * @brief Outdoor siren communication LED blinking period
 */
typedef enum
{
    RBF_OUTDOOR_SIREN_COM_LED_OFF= 0,       /**< Communication LED off */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_1S,    /**< Blink every 1 second */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_2S,    /**< Blink every 2 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_3S,    /**< Blink every 3 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_4S,    /**< Blink every 4 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_5S,    /**< Blink every 5 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_6S,    /**< Blink every 6 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_7S,    /**< Blink every 7 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_8S,    /**< Blink every 8 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_9S,    /**< Blink every 9 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_10S,   /**< Blink every 10 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_15S,   /**< Blink every 15 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_20S,   /**< Blink every 20 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_25S,   /**< Blink every 25 seconds */
    RBF_OUTDOOR_SIREN_COM_LED_PERIOD_30S,   /**< Blink every 30 seconds */
} rbf_outdoor_siren_com_led_period_t;

/**
 * @brief Outdoor siren control parameters
 * Outdoor siren mode represents a persistent state, while outdoor siren action represents an action.
 *  You can use the outdoor siren mode parameter alone to put the outdoor siren into a certain alarm mode,
 * while setting the outdoor siren action to RBF_OUTDOOR_SIREN_CTRL_DISABLED. Alternatively,
 * you can use the outdoor siren action alone to instruct the outdoor siren to perform a specific action,
 * while setting the outdoor siren mode to RBF_OUTDOOR_SIREN_MODE_DISABLED. When you set both the outdoor siren
 * mode and outdoor siren action, the outdoor siren will first execute the action and then enter the outdoor siren mode.
 */
typedef struct
{
    rbf_outdoor_siren_ctrl_action_t action; /**< Outdoor siren control action */
    rbf_outdoor_siren_ctrl_mode_t mode;     /**< Outdoor siren control mode */
} rbf_outdoor_siren_param_t;


/**
 * @brief Group action entry for controlling multiple outdoor sirens simultaneously
 */
typedef struct
{
    rbf_outdoor_siren_ctrl_action_t action; /**< Action to perform */
    uint8_t count_down_time_in_sec;         /**< Countdown time in seconds (used with RBF_OUTDOOR_SIREN_ALARM_COUNT_DOWN) */
    uint8_t no;                             /**< Siren registration number */
} rbf_outdoor_siren_group_actions_t;


/**
 * @brief Outdoor siren configuration settings applied via set/update
 */
typedef struct
{
    rbf_outdoor_siren_volume_t volume;                  /**< Siren volume */
    rbf_outdoor_siren_com_led_period_t com_led_period;  /**< Communication LED blink period */
    rbf_outdoor_siren_ctrl_mode_t mode;                 /**< Alarm mode */
    uint8_t no;                                          /**< Siren registration number */
} rbf_outdoor_siren_configs_t;


/**
 * @brief Callback function to handle outdoor siren device heartbeat events.
 *
 * This function is called whenever an outdoor siren device sends a heartbeat event.
 */
typedef int (*rbf_outdoor_siren_heartbeat_callback_t)(uint8_t no, rbf_outdoor_siren_heartbeat_t* heartbeat);


/**
 * @brief Outdoor siren input status information update callback
 *
 */
typedef int (*rbf_outdoor_siren_input_status_update_callback_t)(uint8_t no, rbf_outdoor_siren_input_status_t* input_status);



/**
 * @brief Outdoor siren callback functions cluster
 *
 */
typedef struct
{
    rbf_outdoor_siren_heartbeat_callback_t hb_cb;                           /**< Heartbeat callback function */
    rbf_outdoor_siren_input_status_update_callback_t input_status_cb;       /**< Input status update callback function */
}rbf_outdoor_siren_callbacks_t;



/**
 * @brief Register outdoor siren callback functions cluster
 *
 * @param cbs  Outdoor siren callback functions cluster
 * @return int 0: Registration successful, -1: Registration failed
 */
int rbf_outdoor_siren_register_callbacks(rbf_outdoor_siren_callbacks_t* cbs);

/**
 * @brief Batch control outdoor sirens through synchronous broadcast
 *
 * @param no_list Outdoor siren number list
 * @param count Number of outdoor sirens
 * @param outdoor_siren_param Outdoor siren control parameters
 * @return int 0: Successfully set outdoor siren broadcast, -1: Failed to set outdoor siren broadcast
 * @par Example:
 * @code
 * uint8_t no_list[3];
 * rbf_outdoor_siren_param_t param;
 *
 * no_list[0] = 1;
 * no_list[1] = 2;
 * no_list[2] = 3;
 * param.action = RBF_OUTDOOR_SIREN_CTRL_DISABLED;
 * param.mode = RBF_OUTDOOR_SIREN_MODE_FIRE_MIXED_ALARM;
 * rbf_outdoor_siren_boardcast_control(no_list, 3, &param);
 * @endcode
 */
int rbf_outdoor_siren_boardcast_control(uint8_t* no_list, unsigned char count, rbf_outdoor_siren_param_t* outdoor_siren_param);


/**
 * @brief Set outdoor siren volume
 *
 * @param no Outdoor siren number
 * @param volume Outdoor siren volume
 * @return int 0: Successfully, -1: Failed
 */
int rbf_outdoor_siren_volume_set(uint8_t no, rbf_outdoor_siren_volume_t volume);


/**
 * @brief Set outdoor siren configuration — takes effect on next sub-device wake-up via synchronous broadcast
 *
 * @param no Outdoor siren registration number
 * @param config Outdoor siren configuration
 * @return int 0: successful, -1: failed
 */
int rbf_outdoor_siren_set(uint8_t no, rbf_outdoor_siren_configs_t* config);

/**
 * @brief Update outdoor siren configuration immediately via broadcast
 *
 * @param no Outdoor siren registration number
 * @param config Outdoor siren configuration
 * @return int 0: successful, -1: failed
 */
int rbf_outdoor_siren_update(uint8_t no, rbf_outdoor_siren_configs_t* config);


/**
 * @brief Callback for outdoor siren volume update notification from the device
 * @param no Device registration number
 * @param volume Current volume setting reported by the siren
 * @return int 0: successful, -1: failed
 */
int rbf_outdoor_siren_volume_update(uint8_t no, rbf_outdoor_siren_volume_t volume);


/**
 * @brief Execute group actions for multiple outdoor sirens immediately
 *
 * @param actions Array of group action entries
 * @param count Number of entries
 * @return int 0: successful, -1: failed
 */
int rbf_outdoor_siren_group_do(rbf_outdoor_siren_group_actions_t* actions, uint8_t count);


#ifdef __cplusplus
}
#endif


#endif
