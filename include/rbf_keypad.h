/**
 * @file rbf_keypad.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Keypad device API — heartbeat, alarm status, key input, settings, and action control
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef RBF_KEYPAD_H
#define RBF_KEYPAD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif



/**
 * @brief Structure to represent a keypad device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Keypad battery level 0-100 */
    int32_t rssi;   /**< Keypad RSSI */
}rbf_keypad_heartbeat_t;


/**
 * @brief Keypad alarm information
 *
 */
typedef struct
{
    uint8_t emergency_alarm;  /**< Keypad emergency alarm status: 0 - emergency alarm clear, 1 - emergency alarm */
    uint8_t fire_alarm;       /**< Keypad fire alarm status: 0 - fire alarm clear, 1 - fire alarm */
    uint8_t medical_alarm;    /**< Keypad medical alarm status: 0 - medical alarm clear, 1 - medical alarm */
    uint8_t tamper;           /**< Keypad tamper status: 0 - tamper normal, 1 - tamper alarm  */
}rbf_keypad_alarm_status_t;


/**
 * @brief Keypad alarm tone type
 */
typedef enum
{
    RBF_KEYPAD_ALARM_TONE_NONE = 0,   /**< No alarm tone */
    RBF_KEYPAD_ALARM_TONE_INTRUSION,  /**< Invasion alarm tone */
    RBF_KEYPAD_ALARM_TONE_FIRE,       /**< Fire alarm tone */
    RBF_KEYPAD_ALARM_TONE_EMERGENCY,  /**< Emergency alarm tone */
    RBF_KEYPAD_ALARM_TONE_MEDICAL,    /**< Medical alarm tone */
}rbf_keypad_alarm_tone_type_t;


/**
 * @brief Keypad backlight duration after wake-up
 */
typedef enum
{
    RBF_KEYPAD_BACKLIGHT_TIME_10S = 0, /**< Backlight 10 seconds */
    RBF_KEYPAD_BACKLIGHT_TIME_15S,     /**< Backlight 15 seconds */
    RBF_KEYPAD_BACKLIGHT_TIME_20S,     /**< Backlight 20 seconds */
    RBF_KEYPAD_BACKLIGHT_TIME_25S,     /**< Backlight 25 seconds */
}rbf_keypad_backlight_time_t;

/**
 * @brief Keypad settings — takes effect on next wake-up
 */
typedef struct
{
    rbf_keypad_alarm_tone_type_t alarm_tone_play; /**< Alarm tone to play */
    uint8_t err_led_state;                        /**< Error LED: 0-off when wakeup, 1-on when wakeup */
    uint8_t arm_led_state;                        /**< Arm LED: 0-off when wakeup, 1-on when wakeup */
    uint8_t warn_led_state;                       /**< Warn LED: 0-off when wakeup, 1-on when wakeup, 2-blink when wakeup */
    uint8_t key_tone_enable;                      /**< Key tone when pressed: 0-disable, 1-enable */
    rbf_keypad_backlight_time_t backlight_time;   /**< Backlight duration time */
    uint8_t lock_state;                           /**< Keypad lock: 0-unlock, 1-lock */
    uint8_t local_enable;                         /**< Local arming control enable: 0-disable, 1-enable */
    uint8_t emergency_voice_enable;               /**< Emergency alarm voice prompt: 0-disable, 1-enable */
    uint8_t medical_voice_enable;                 /**< Medical alarm voice prompt: 0-disable, 1-enable */
    uint8_t sounder_enable;                       /**< Sounder relay output: 0-disable, 1-enable */
}rbf_keypad_settings_t;


/**
 * @brief Keypad action command — immediate one-shot operations
 *
 * Action values 0-5 control alarm sounds. Action values 10-15 control recovery/close indications with beep + LED feedback.
 */
typedef enum
{
    RBF_KEYPAD_ACTION_TURN_OFF = 0,                            /**< Turn off */
    RBF_KEYPAD_ACTION_INTRUSION_SOUND,                         /**< Invasion alarm sound */
    RBF_KEYPAD_ACTION_119_SOUND,                               /**< Fire alarm sound */
    RBF_KEYPAD_ACTION_110_SOUND,                               /**< Emergency alarm sound */
    RBF_KEYPAD_ACTION_120_SOUND,                               /**< Medical alarm sound */
    RBF_KEYPAD_ACTION_SOUND_TWICE_LEDGREEN_TWICE_RECOVER = 10, /**< Beep twice, green LED flash twice, recover */
    RBF_KEYPAD_ACTION_SOUND_TWICE_RECOVER,                     /**< Beep twice, recover */
    RBF_KEYPAD_ACTION_SOUND_TWICE_LEDGREEN_TWICE_CLOSE,        /**< Beep twice, green LED flash twice, close */
    RBF_KEYPAD_ACTION_SOUND_TWICE_CLOSE,                       /**< Beep twice, close */
    RBF_KEYPAD_ACTION_SOUND_THIRD_RECOVER,                     /**< Beep three times, recover */
    RBF_KEYPAD_ACTION_SOUND_THIRD_CLOSE                        /**< Beep three times, close */
}rbf_keypad_action_t;


/**
 * @brief Keypad heartbeat callback handler
 * @param no Device registration number
 * @param heartbeat Heartbeat information
 */
typedef int (*rbf_keypad_heartbeat_callback_t)(uint8_t no, rbf_keypad_heartbeat_t* heartbeat);


/**
 * @brief Keypad alarm callback handler
 * @param no   Registration number of the keypad sub-device
 * @param alarm_status  Keypad alarm state
 */
typedef int (*rbf_keypad_alarm_callback_t)(uint8_t no, rbf_keypad_alarm_status_t* alarm_status);



/**
 * @brief Keypad key press callback handler
 * @param no   Registration number of the keypad sub-device
 * @param input_keys  The keypad key values in the order they were pressed
 * @param input_count  Keypad input count
 */
typedef int (*rbf_keypad_key_input_callback_t)(uint8_t no, uint8_t input_keys[32], uint8_t input_count);

/**
 * @brief Keypad callback functions cluster
 *
 */
typedef struct
{
    rbf_keypad_heartbeat_callback_t hb_cb;           /**< Heartbeat callback function  */
    rbf_keypad_alarm_callback_t alarm_cb;            /**< Alarm callback function */
    rbf_keypad_key_input_callback_t key_input_cb;    /**< Key press callback function */
}rbf_keypad_callbacks_t;


/**
 * @brief Register keypad callback functions cluster
 *
 * @param cbs Keypad callback functions cluster
 * @return int 0: Registration successful, -1: Registration failed
 */
int rbf_keypad_register_callbacks(rbf_keypad_callbacks_t* cbs);


/**
 * @brief Set keypad settings — takes effect on next keypad wake-up via synchronous broadcast
 *
 * @param no Device registration number
 * @param settings Keypad settings
 * @return int 0: successful, -1: failed
 */
int rbf_keypad_set(uint8_t no, rbf_keypad_settings_t* settings);


/**
 * @brief Update keypad settings immediately via broadcast
 *
 * @param no Device registration number
 * @param settings Keypad settings
 * @return int 0: successful, -1: failed
 */
int rbf_keypad_update(uint8_t no, rbf_keypad_settings_t* settings);


/**
 * @brief Send an immediate action command to the keypad (alarm sound, beep + LED indication)
 *
 * @param no Device registration number
 * @param action Keypad action to execute
 * @return int 0: successful, -1: failed
 */
int rbf_keypad_prepare(uint8_t no, rbf_keypad_action_t action);

#ifdef __cplusplus
}
#endif



#endif
