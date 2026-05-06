/**
 * @file rbf_api_ex.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Extended RBF API — production testing, certification, batch settings, and advanced hub/sub-device configuration
 * @version 0.1
 * @date 2025-09-04
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef RBF_API_EX_H
#define RBF_API_EX_H

#include "rbf_api.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief IO device arming/disarming setting entry (no and status pair)
 */
typedef struct
{
    int no;                         /**< IO device registration number */
    RBF_io_alarm_status_t status;   /**< Arming/disarming status */
}RBF_io_alarm_setting_t;


/**
 * @brief Sounder control action — one-shot alarm behaviors
 */
typedef enum
{
    RBF_SOUNDER_CTRL_DISABLED = 0,      /**< No action */
    RBF_SOUNDER_LIGHT_ALARM_ONCE,       /**< Flash light alarm once */
    RBF_SOUNDER_SOUND_ALARM_ONCE,       /**< Sound alarm once */
    RBF_SOUNDER_MIXED_ALARM_ONCE,       /**< Mixed light+sound alarm once */
    RBF_SOUNDER_LIGHT_ALARM_TWICE,      /**< Flash light alarm twice */
    RBF_SOUNDER_SOUND_ALARM_TWICE,      /**< Sound alarm twice */
    RBF_SOUNDER_MIXED_ALARM_TWICE,      /**< Mixed light+sound alarm twice */
    RBF_SOUNDER_ALARM_COUNT_DOWN,       /**< Countdown alarm */
} rbf_sounder_ctrl_action_t;


/**
 * @brief Sounder control mode — persistent alarm states
 */
typedef enum
{
    RBF_SOUNDER_MODE_DISABLED = 0,              /**< Alarm mode disabled */
    RBF_SOUNDER_MODE_INVASION_LIGHT_ALARM,      /**< Invasion light alarm mode */
    RBF_SOUNDER_MODE_INVASION_SOUND_ALARM,      /**< Invasion sound alarm mode */
    RBF_SOUNDER_MODE_INVASION_MIXED_ALARM,      /**< Invasion mixed alarm mode */
    RBF_SOUNDER_MODE_FIRE_LIGHT_ALARM,          /**< Fire light alarm mode */
    RBF_SOUNDER_MODE_FIRE_SOUND_ALARM,          /**< Fire sound alarm mode */
    RBF_SOUNDER_MODE_FIRE_MIXED_ALARM,          /**< Fire mixed alarm mode */
    RBF_SOUNDER_MODE_EMERGENCY_LIGHT_ALARM,     /**< Emergency light alarm mode */
    RBF_SOUNDER_MODE_EMERGENCY_SOUND_ALARM,     /**< Emergency sound alarm mode */
    RBF_SOUNDER_MODE_EMERGENCY_MIXED_ALARM,     /**< Emergency mixed alarm mode */
    RBF_SOUNDER_MODE_MEDICAL_LIGHT_ALARM,       /**< Medical light alarm mode */
    RBF_SOUNDER_MODE_MEDICAL_SOUND_ALARM,       /**< Medical sound alarm mode */
    RBF_SOUNDER_MODE_MEDICAL_MIXED_ALARM,       /**< Medical mixed alarm mode */
} rbf_sounder_ctrl_mode_t;


/**
 * @brief Sounder control parameters
 * Sounder mode represents a persistent state, while sounder action represents an action.
 *  You can use the sounder mode parameter alone to put the sounder into a certain alarm mode,
 * while setting the sounder action to RBF_SOUNDER_CTRL_DISABLED. Alternatively,
 * you can use the sounder action alone to instruct the sounder to perform a specific action,
 * while setting the sounder mode to RBF_SOUNDER_MODE_DISABLED. When you set both the sounder
 * mode and sounder action, the sounder will first execute the action and then enter the sounder mode.
 */
typedef struct
{
    rbf_sounder_ctrl_action_t action; /**< Sounder control action */
    rbf_sounder_ctrl_mode_t mode;     /**< Sounder control mode */
} rbf_sounder_param_t;


/**
 * @brief Group action entry for controlling multiple sounders simultaneously
 */
typedef struct
{
    rbf_sounder_ctrl_action_t action;               /**< Action to perform */
    uint8_t count_down_time_in_sec;                  /**< Countdown time in seconds (used with RBF_SOUNDER_ALARM_COUNT_DOWN) */
    uint8_t no;                                      /**< Sounder registration number */
} rbf_sounder_group_actions_t;

/**
 * @brief Sounder setting entry pairing a device number with its control parameters
 */
typedef struct
{
    int no;                         /**< Sounder registration number */
    rbf_sounder_param_t param;      /**< Sounder control parameters */
}RBF_sounder_setting_t;


#define MAX_IO_ALARM_COUNT      (128)   /**< Maximum number of IO alarm settings in a batch */
#define MAX_SOUNDER_COUNT        (12)   /**< Maximum number of sounder settings in a batch */
#define MAX_UPDATEME_COUNT       (12)   /**< Maximum number of UpdateMe devices in a batch */

/**
 * @brief Batch settings for sub-devices — combines IO alarm, sounder, and UpdateMe settings in one call
 */
typedef struct
{
    RBF_io_alarm_setting_t io_alarms[MAX_IO_ALARM_COUNT];       /**< IO alarm settings array */
    int io_count;                                                /**< Number of IO alarm entries */
    RBF_sounder_setting_t sounder_param[MAX_SOUNDER_COUNT];     /**< Sounder settings array */
    int sounder_count;                                           /**< Number of sounder entries */
    RBF_dev_id_t updateme_devs[MAX_UPDATEME_COUNT];             /**< UpdateMe device list */
    int updateme_dev_count;                                      /**< Number of UpdateMe devices */
}RBF_subdev_batch_settings_t;


/**
 * @brief QRFH (Quick Response Frequency Hopping) configuration data for a sub-device
 */
typedef struct
{
    unsigned char isRxWake;     /**< RX wake enable: 0-disable, 1-enable */
    unsigned char isMaxPower;   /**< Maximum transmit power enable */
    unsigned char isAutoPower;  /**< Auto power control enable */
    unsigned char ioEn;         /**< For input devices (detectors): enable input detection (arming). For output devices: configure output state On/Off */
    unsigned char isFileTx;     /**< File transmission mode enable */
    unsigned char isUm;         /**< UpdateMe mode enable */
    unsigned char isFm;         /**< FindMe mode enable */
    unsigned char isRssi;       /**< RSSI reporting enable */
    unsigned char isRxAlways;   /**< Always-on RX enable */
}RBF_qrfh_data_t;


/**
 * @brief QRFH setting entry pairing a device with its QRFH data
 */
typedef struct
{
    RBF_dev_cat_t cat;          /**< Device category */
    int no;                     /**< Device registration number */
    RBF_qrfh_data_t qrfh;       /**< QRFH configuration data */
}RBF_qrfh_setting_t;

/**
 * @brief Set the hub with extended parameters including custom code
 *
 * @param freq  Currently supports RBF_FREQ_868/RBF_FREQ_915/RBF_FREQ_433/RBF_FREQ_916/RBF_FREQ_WPC_868/RBF_FREQ_MAL_915
 * @param jamming_threshold Jamming threshold default-0
 * @param cust_code Customer code, default-0
 * @return int 0: Setting successful, -1: Setting failed
 */
int rbf_set_hub_ex(RBF_Freq_t freq, unsigned char jamming_threshold, unsigned int cust_code);


/**
 * @brief Start carrier transmission
 *
 * @param channel Carrier transmission channel
 * @param power The actual transmit power is power divided by 10.
 * @param type Wave type
 * @param index Carrier transmit antenna selection
 * @return int 0: successful, -1: failed
 */
int rbf_send_carrier_ex(int channel, int power, RBF_wave_type_t type, RBF_ant_index_t index);


/**
 * @brief Stop carrier transmission
 *
 * @return int 0: successful, -1: failed
 */
int rbf_send_carrier_stop_ex();


/**
 * @brief Set hub PANID
 *
 * @param panid Hub PANID to set
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_panid_ex(unsigned int panid);

/**
 * @brief Get hub PANID
 *
 * @param panid Returned hub PANID
 * @return int 0: successful, -1: failed
 */
int rbf_get_hub_panid_ex(unsigned int* panid);



/**
 * @brief Blocking get hub version string
 *
 * @param version_str Returned hub version string
 * @return int 0: successful, -1: failed
 */
int rbf_get_hub_version_ex(char* version_str);



/**
 * @brief Obtain the ADC acquisition values of the hub terminal voltage and resistance.
 *
 * @param vol Battery voltage in millivolts (mV) vol = vol[0]*1000 + vol[1]*10
 * @param res Battery resistance value  res = res[0]*10000 + res[1]*100
 * @return int 0: successful, -1: failed
 */
int rbf_get_hub_vol_res_ex(int* vol, int* res);

/**
 * @brief Blocking get hub background noise
 *
 * @param avg_rssi Average background noise
 * @param real_rssi Real-time background noise
 * @return int 0: successful, -1: failed
 */
int rbf_get_hub_rssi_ex(int* avg_rssi, int* real_rssi);


/**
 * @brief High-frequency crystal oscillator adjustment frequency offset
 *
 * @param freq Frequency offset value
 * @return int 0: successful, -1: failed
 */
int rbf_test_high_frequency_adjust_ex(int freq);

/**
 * @brief Low-frequency crystal oscillator adjustment frequency offset
 *
 * @param freq Frequency offset value
 * @return int 0: successful, -1: failed
 */
int rbf_test_low_frequency_adjust_ex(int freq);



/**
 * @brief Low-frequency crystal oscillator mapped to PA0 pin output
 *
 * @param enable 1: enable 0: disable
 * @return int 0: successful, -1: failed
 */
int rbf_test_pa0_output_ex(int enable);


/**
 * @brief Set hub sub-device frequency band
 *
 * @param freq Frequency band to set
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_freq_ex(RBF_Freq_t freq);

/**
 * @brief Set hub sub-device custom code
 *
 * @param cust_code Customer code
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_custcode_ex(unsigned int cust_code);

/**
 * @brief Enable or disable RSSI reporting for a specific sub-device
 *
 * @param dev_id Sub-device ID
 * @param enable 1: enable, 0: disable
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_rssi_oder_ex(RBF_dev_id_t* dev_id, int enable);

/**
 * @brief Enable or disable FindMe mode for a specific sub-device
 *
 * @param dev_id Sub-device ID
 * @param enable 1: enable, 0: disable
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_findme_oder_ex(RBF_dev_id_t* dev_id, int enable);

/**
 * @brief Enable or disable test mode for a specific sub-device
 *
 * @param dev_id Sub-device ID
 * @param enable 1: enable, 0: disable
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_test_oder_ex(RBF_dev_id_t* dev_id, int enable);

/**
 * @brief Batch set hub sub-device configurations including IO alarms, sounders, and UpdateMe
 *
 * @param settings Batch settings structure
 * @return int 0: successful, -1: failed
 */
int rbf_batch_set_hub_subdev_ex(RBF_subdev_batch_settings_t* settings);

/**
 * @brief Set QRFH parameters for a specific sub-device
 *
 * @param dev_id Sub-device ID
 * @param qrfh QRFH configuration data
 * @return int 0: successful, -1: failed
 */
int rbf_set_hub_subdev_qrfh_ex(RBF_dev_id_t* dev_id, RBF_qrfh_data_t* qrfh);

/**
 * @brief Execute group actions for multiple sounders immediately
 *
 * @param actions Array of group action entries
 * @param count Number of entries
 * @return int 0: successful, -1: failed
 */
int rbf_sounder_group_do_ex(rbf_sounder_group_actions_t* actions, uint8_t count);

/**
 * @brief Prepare group actions for multiple sounders without immediate execution
 *
 * @param actions Array of group action entries
 * @param count Number of entries
 * @return int 0: successful, -1: failed
 */
int rbf_sounder_group_prepare_ex(rbf_sounder_group_actions_t* actions, uint8_t count);

#ifdef __cplusplus
}
#endif


#endif
