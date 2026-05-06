/**
 * @file rbf_indoor_siren.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Indoor siren device API — heartbeat, input status, volume control, alarm action/mode, and broadcast control
 * @version 0.1
 * @date 2025-01-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef RBF_INDOOR_SIREN_H
#define RBF_INDOOR_SIREN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @brief Indoor siren volume level
 *
 */
typedef enum
{
    RBF_INDOOR_SIREN_VOLUME_LOW = 0,
    RBF_INDOOR_SIREN_VOLUME_MID,
    RBF_INDOOR_SIREN_VOLUME_HIGH,
} rbf_indoor_siren_volume_t;

/**
 * @brief Structure to represent an indoor siren device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Indoor siren battery level 0-100 */
    int32_t rssi;   /**< Indoor siren RSSI */
}rbf_indoor_siren_heartbeat_t;


/**
 * @brief Indoor siren status information
 *
 */
typedef struct
{
    uint8_t battery_fault; /**< Battery status: 0 - Battery connected, 1 - Battery not connected */
    uint8_t tamper;        /**< Tamper status: 0 - Tamper normal, 1 - Tamper alarm */
}rbf_indoor_siren_input_status_t;

/**
 * @brief Indoor siren control action — one-shot alarm behaviors
 */
typedef enum
{
    RBF_INDOOR_SIREN_CTRL_DISABLED = 0,     /**< No action */
    RBF_INDOOR_SIREN_LIGHT_ALARM_ONCE,      /**< Flash light alarm once */
    RBF_INDOOR_SIREN_SOUND_ALARM_ONCE,      /**< Sound alarm once */
    RBF_INDOOR_SIREN_MIXED_ALARM_ONCE,      /**< Mixed light+sound alarm once */
    RBF_INDOOR_SIREN_LIGHT_ALARM_TWICE,     /**< Flash light alarm twice */
    RBF_INDOOR_SIREN_SOUND_ALARM_TWICE,     /**< Sound alarm twice */
    RBF_INDOOR_SIREN_MIXED_ALARM_TWICE,     /**< Mixed light+sound alarm twice */
} rbf_indoor_siren_ctrl_action_t;


/**
 * @brief Indoor siren control mode — persistent alarm states
 */
typedef enum
{
    RBF_INDOOR_SIREN_MODE_DISABLED = 0,             /**< Alarm mode disabled */
    RBF_INDOOR_SIREN_MODE_INVASION_LIGHT_ALARM,     /**< Invasion light alarm mode */
    RBF_INDOOR_SIREN_MODE_INVASION_SOUND_ALARM,     /**< Invasion sound alarm mode */
    RBF_INDOOR_SIREN_MODE_INVASION_MIXED_ALARM,     /**< Invasion mixed alarm mode */
    RBF_INDOOR_SIREN_MODE_FIRE_LIGHT_ALARM,         /**< Fire light alarm mode */
    RBF_INDOOR_SIREN_MODE_FIRE_SOUND_ALARM,         /**< Fire sound alarm mode */
    RBF_INDOOR_SIREN_MODE_FIRE_MIXED_ALARM,         /**< Fire mixed alarm mode */
    RBF_INDOOR_SIREN_MODE_EMERGENCY_LIGHT_ALARM,    /**< Emergency light alarm mode */
    RBF_INDOOR_SIREN_MODE_EMERGENCY_SOUND_ALARM,    /**< Emergency sound alarm mode */
    RBF_INDOOR_SIREN_MODE_EMERGENCY_MIXED_ALARM,    /**< Emergency mixed alarm mode */
    RBF_INDOOR_SIREN_MODE_MEDICAL_LIGHT_ALARM,      /**< Medical light alarm mode */
    RBF_INDOOR_SIREN_MODE_MEDICAL_SOUND_ALARM,      /**< Medical sound alarm mode */
    RBF_INDOOR_SIREN_MODE_MEDICAL_MIXED_ALARM,      /**< Medical mixed alarm mode */
} rbf_indoor_siren_ctrl_mode_t;




/**
 * @brief Indoor siren communication LED blinking period
 */
typedef enum
{
    RBF_INDOOR_SIREN_COM_LED_OFF= 0,        /**< Communication LED off */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_1S,     /**< Blink every 1 second */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_2S,     /**< Blink every 2 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_3S,     /**< Blink every 3 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_4S,     /**< Blink every 4 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_5S,     /**< Blink every 5 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_6S,     /**< Blink every 6 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_7S,     /**< Blink every 7 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_8S,     /**< Blink every 8 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_9S,     /**< Blink every 9 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_10S,    /**< Blink every 10 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_15S,    /**< Blink every 15 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_20S,    /**< Blink every 20 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_25S,    /**< Blink every 25 seconds */
    RBF_INDOOR_SIREN_COM_LED_PERIOD_30S,    /**< Blink every 30 seconds */
} rbf_indoor_siren_com_led_period_t;

/**
 * @brief Indoor siren control parameters
 * Indoor siren mode represents a persistent state, while indoor siren action represents an action.
 *  You can use the indoor siren mode parameter alone to put the indoor siren into a certain alarm mode,
 * while setting the indoor siren action to RBF_INDOOR_SIREN_CTRL_DISABLED. Alternatively,
 * you can use the indoor siren action alone to instruct the indoor siren to perform a specific action,
 * while setting the indoor siren mode to RBF_INDOOR_SIREN_MODE_DISABLED. When you set both the indoor siren
 * mode and indoor siren action, the indoor siren will first execute the action and then enter the indoor siren mode.
 */
typedef struct
{
    rbf_indoor_siren_ctrl_action_t action; /**< Indoor siren control action */
    rbf_indoor_siren_ctrl_mode_t mode;     /**< Indoor siren control mode */
} rbf_indoor_siren_param_t;


/**
 * @brief Indoor siren configuration settings applied via set/update
 */
typedef struct
{
    rbf_indoor_siren_volume_t volume;                   /**< Siren volume */
    rbf_indoor_siren_com_led_period_t com_led_period;   /**< Communication LED blink period */
    rbf_indoor_siren_ctrl_mode_t mode;                  /**< Alarm mode */
    uint8_t no;                                          /**< Siren registration number */
} rbf_indoor_siren_configs_t;


/**
 * @brief Callback function to handle indoor siren device heartbeat events.
 *
 * This function is called whenever an indoor siren device sends a heartbeat event.
 */
typedef int (*rbf_indoor_siren_heartbeat_callback_t)(uint8_t no, rbf_indoor_siren_heartbeat_t* heartbeat);


/**
 * @brief Callback for indoor siren volume update notification
 * @param no Device registration number
 * @param volume Current volume setting reported by the siren
 */
typedef int (*rbf_indoor_siren_volume_update_callback_t)(uint8_t no, rbf_indoor_siren_volume_t volume);
/**
 * @brief Indoor siren input status information update callback
 *
 */
typedef int (*rbf_indoor_siren_input_status_update_callback_t)(uint8_t no, rbf_indoor_siren_input_status_t* input_status);



/**
 * @brief Indoor siren callback functions cluster
 *
 */
typedef struct
{
    rbf_indoor_siren_heartbeat_callback_t hb_cb;                               /**< Heartbeat callback function */
    rbf_indoor_siren_input_status_update_callback_t input_status_cb;           /**< Input status update callback function */
    rbf_indoor_siren_volume_update_callback_t volume_update_cb;                /**< Volume update callback function */
}rbf_indoor_siren_callbacks_t;



/**
 * @brief Register indoor siren callback functions cluster
 *
 * @param cbs  Indoor siren callback functions cluster
 * @return int 0: Registration successful, -1: Registration failed
 */
int rbf_indoor_siren_register_callbacks(rbf_indoor_siren_callbacks_t* cbs);

/**
 * @brief Batch control indoor sirens through synchronous broadcast
 *
 * @param no_list Indoor siren number list
 * @param count Number of indoor sirens
 * @param indoor_siren_param Indoor siren control parameters
 * @return int 0: Successfully set indoor siren broadcast, -1: Failed to set indoor siren broadcast
 * @par Example:
 * @code
 * uint8_t no_list[3];
 * rbf_indoor_siren_param_t param;
 *
 * no_list[0] = 1;
 * no_list[1] = 2;
 * no_list[2] = 3;
 * param.action = RBF_INDOOR_SIREN_CTRL_DISABLED;
 * param.mode = RBF_INDOOR_SIREN_MODE_FIRE_MIXED_ALARM;
 * rbf_indoor_siren_boardcast_control(no_list, 3, &param);
 * @endcode
 */
int rbf_indoor_siren_boardcast_control(uint8_t* no_list, unsigned char count, rbf_indoor_siren_param_t* indoor_siren_param);


/**
 * @brief Set indoor siren volume
 *
 * @param no Indoor siren number
 * @param volume Indoor siren volume
 * @return int 0: Successfully, -1: Failed
 */
int rbf_indoor_siren_volume_set(uint8_t no, rbf_indoor_siren_volume_t volume);


/**
 * @brief Set indoor siren configuration — takes effect on next sub-device wake-up via synchronous broadcast
 *
 * @param no Indoor siren registration number
 * @param config Indoor siren configuration
 * @return int 0: successful, -1: failed
 */
int rbf_indoor_siren_set(uint8_t no, rbf_indoor_siren_configs_t* config);

/**
 * @brief Update indoor siren configuration immediately via broadcast
 *
 * @param no Indoor siren registration number
 * @param config Indoor siren configuration
 * @return int 0: successful, -1: failed
 */
int rbf_indoor_siren_update(uint8_t no, rbf_indoor_siren_configs_t* config);

#ifdef __cplusplus
}
#endif


#endif
