/**
 * @file rbf_api_ex.h
 * @author Jio (hedajun@hzdusun.com)
 * @brief rbf_api_ex is an extension of rbf_api, 
 *     providing more advanced functional interfaces
 *     Supports production testing, certification, 
 *     and other scenarios
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
 * @brief Set the hub with extended parameters
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
 * @param type wave type
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
 * @param panid Hub pandID to set
 * @return int int 0: successful, -1: failed
 */
int rbf_set_hub_panid_ex(unsigned int panid);

/**
 * @brief Get hub PANID
 * 
 * @param panid Returned hub pandID
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
 * @param freq 
 * @return int 0: successful, -1: failed
 */
int rbf_test_high_frequency_adjust_ex(int freq);

/**
 * @brief Low-frequency crystal oscillator adjustment frequency offset
 * 
 * @param freq 
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




#ifdef __cplusplus
}
#endif


#endif