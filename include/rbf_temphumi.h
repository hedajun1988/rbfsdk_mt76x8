/**
 * @file rbf_temphumi.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief Temperature and humidity sensor API — heartbeat with temp/humi readings, threshold alarms, and configuration
 * @version 0.1
 * @date 2024-12-11
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef RBF_TEMP_HUMI_H
#define RBF_TEMP_HUMI_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Structure to represent a temperature and humidity sensor device heartbeat event.
 */
typedef struct
{
    uint8_t power;  /**< Temperature and humidity sensor battery level 0-100 */
    float temp;     /**< Temperature value */
    float humi;     /**< Humidity value */
    int32_t rssi;   /**< Sensor RSSI */
}rbf_temp_humi_heartbeat_t;

/**
 * @brief Temperature and humidity sensor threshold alarm status
 *
 */
typedef struct
{
    uint8_t over_temp_alarm;  /**< Over-temperature alarm: 0 - recovered, 1 - over temperature detected */
    uint8_t low_temp_alarm;   /**< Low-temperature alarm: 0 - recovered, 1 - low temperature detected  */
    uint8_t over_humi_alarm;  /**< Over-humidity alarm: 0 - recovered, 1 - over humidity detected */
    uint8_t low_humi_alarm;   /**< Low-humidity alarm: 0 - recovered, 1 - low humidity detected */
}rbf_temp_humi_status_t;


/**
 * @brief Temperature unit selection
 */
typedef enum
{
    RBF_TEMP_UINT_CELS = 0, /**< Celsius */
    RBF_TEMP_UINT_FAHR,     /**< Fahrenheit */
}rbf_temp_humi_temp_uint_t;


/**
 * @brief Temperature change reporting threshold — triggers a report when temperature changes by this amount
 */
typedef enum
{
    RBF_TEMP_REPORT_0_5_CHANGE = 0, /**< Report on 0.5 degree change */
    RBF_TEMP_REPORT_1_CHANGE,       /**< Report on 1 degree change */
    RBF_TEMP_REPORT_5_CHANGE,       /**< Report on 5 degree change */
    RBF_TEMP_REPORT_10_CHANGE,      /**< Report on 10 degree change */
}rbf_temp_humi_temp_report_threshold_t;

/**
 * @brief Humidity change reporting threshold — triggers a report when humidity changes by this amount
 */
typedef enum
{
    RBF_HUMI_REPORT_5_CHANGE = 0,   /**< Report on 5% change */
    RBF_HUMI_REPORT_10_CHANGE,      /**< Report on 10% change */
    RBF_HUMI_REPORT_15_CHANGE,      /**< Report on 15% change */
    RBF_HUMI_REPORT_20_CHANGE,      /**< Report on 20% change */
}rbf_temp_humi_humi_report_threshold_t;


/**
 * @brief Signal strength level thresholds for reporting
 */
typedef enum
{
    RBF_HUMI_SIGNAL_LOCAL = 0,  /**< Use local device setting */
    RBF_HUMI_SIGNAL_LV1,        /**< Signal level 1 */
    RBF_HUMI_SIGNAL_LV2,        /**< Signal level 2 */
    RBF_HUMI_SIGNAL_LV3,        /**< Signal level 3 */
    RBF_HUMI_SIGNAL_LV4,        /**< Signal level 4 */
}rbf_temp_humi_signal_level_t;

/**
 * @brief Battery level thresholds for reporting
 */
typedef enum
{
    RBF_HUMI_BATTERY_LOCAL = 0, /**< Use local device setting */
    RBF_HUMI_BATTERY_LV1,       /**< Battery level 1 */
    RBF_HUMI_BATTERY_LV2,       /**< Battery level 2 */
    RBF_HUMI_BATTERY_LV3,       /**< Battery level 3 */
    RBF_HUMI_BATTERY_LV4,       /**< Battery level 4 */
}rbf_temp_humi_battery_level_t;

/**
 * @brief Temperature and humidity sensor configuration
 */
typedef struct
{
    rbf_temp_humi_temp_uint_t temp_units;                   /**< Temperature units (Celsius/Fahrenheit) */
    rbf_temp_humi_temp_report_threshold_t temp_threshold;   /**< Temperature change reporting threshold */
    rbf_temp_humi_humi_report_threshold_t humi_threshold;   /**< Humidity change reporting threshold */
    rbf_temp_humi_signal_level_t signal;                    /**< Signal strength reporting level */
    rbf_temp_humi_battery_level_t battery;                  /**< Battery reporting level */
}rbf_temp_humi_config_t;

/**
 * @brief Callback function to handle temp/humi device heartbeat events.
 *
 * This function is called whenever a temp/humi device sends a heartbeat event.
 */
typedef int (*rbf_temp_humi_heartbeat_callback_t)(uint8_t no, rbf_temp_humi_heartbeat_t* heartbeat);


/**
 * @brief Callback for updating temp/humi threshold alarm status
 *
 */
typedef int (*rbf_temp_humi_input_status_update_callback_t)(uint8_t no, rbf_temp_humi_status_t* input_status);



/**
 * @brief Temperature and humidity sensor callback functions cluster
 *
 */
typedef struct
{
    rbf_temp_humi_heartbeat_callback_t hb_cb;                               /**< Heartbeat callback */
    rbf_temp_humi_input_status_update_callback_t input_status_cb;           /**< Threshold alarm status callback */
}rbf_temp_humi_callbacks_t;



/**
 * @brief Register temperature and humidity sensor callback functions cluster
 *
 * @param cbs Temperature and humidity sensor callback functions cluster
 * @return int 0 - Registration successful, -1 - Registration failed
 */
int rbf_temp_humi_register_callbacks(rbf_temp_humi_callbacks_t* cbs);


/**
 * @brief Set temperature and humidity sensor configuration — takes effect on next sub-device wake-up
 *
 * @param no Temperature and humidity sensor number
 * @param config Temperature and humidity sensor configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_temp_humi_set(uint8_t no, rbf_temp_humi_config_t* config);



/**
 * @brief Update temperature and humidity sensor configuration immediately via broadcast
 *
 * @param no Temperature and humidity sensor number
 * @param config Temperature and humidity sensor configuration
 * @return int 0: Successfully, -1: Failed
 */
int rbf_temp_humi_update(uint8_t no, rbf_temp_humi_config_t* config);

#ifdef __cplusplus
}
#endif

#endif
