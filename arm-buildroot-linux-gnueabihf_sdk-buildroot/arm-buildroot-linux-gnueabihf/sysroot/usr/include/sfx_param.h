/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * sfx_param.h -- sfx for param
 *
 * Dby <dby@allwinnertech.com>
 *
 * Copyright (c) 2024 Allwinnertech Ltd.
 */

#ifndef __SFX_PARAM_H
#define __SFX_PARAM_H

#include "sfx_list.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/* !!! key&val string must end with '\n' !!! */
/* !!! do not use para adjust service at the same time when use the adjust param in this way !!! */

/* string must conform to json format, and in the child of param, the key must same as xml */
/* eg.
/* string: {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":0}}
 * json format:
 * {
 * 	"dev_name":"Speaker",
 * 	"ap_name":"VOLUME",
 * 	"ap_sub_id":0,
 * 	"setup_mode":0,
 * 	"param_type":"en",
 * 	"param":{
 * 		"enable":0
 * 	}
 *}
 */

/****** volume ******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":0}}
 * {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 *
 * KV2: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"dB_max":0,"dB_min":-80,"level_max":100,"level_min":0,"ch_cnt":2,"ch_volume_0":5,"ch_volume_1":10}}
 *
 * KV3: "param_type":"vol"
 * if param_type is vol, must support ch_cnt!!!
 *
 * eg.
 * {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"vol","param":{"ch_cnt":2,"ch_volume_0":10,"ch_volume_1":20}}
 * {"dev_name":"Speaker","ap_name":"VOLUME","ap_sub_id":0,"setup_mode":0,"param_type":"vol","param":{"ch_cnt":2,"ch_volume_1":20}}
 *
 */

/****** delay ******
* KV1: "param_type":"en"
 * eg.
 * {"dev_name":"Speaker","ap_name":"DELAY","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
* KV2: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"DELAY","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"delay_unit":0,"delay_max":1500,"ch_cnt":2,"ch0_delay":500,"ch1_delay":1000}}
 */

/****** pass filter ******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"Speaker","ap_name":"PASS_FILTER","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"hpf"
 * {"dev_name":"Speaker","ap_name":"PASS_FILTER","ap_sub_id":0,"setup_mode":0,"param_type":"hpf","param":{"ch_cnt":2,"hpf_slope_0":6,"hpf_slope_1":6,"hpf_freq_0":50,"hpf_freq_1":50}}
 *
 * KV3: "param_type":"lpf"
 * {"dev_name":"Speaker","ap_name":"PASS_FILTER","ap_sub_id":0,"setup_mode":0,"param_type":"lpf","param":{"ch_cnt":2,"lpf_slope_0":48,"lpf_slope_1":48,"lpf_freq_0":23000,"lpf_freq_1":23000}}
 *
 * KV4: "param_type":"all"
 * "hpf_type" and "lpf_type" are essential. If you don't use it, then configure it as "null".
 * eg.
 * {"dev_name":"Speaker","ap_name":"PASS_FILTER","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"hpf_type":"butterworth","lpf_type":"butterworth","ch_cnt":2,"hpf_slope_0":6,"hpf_slope_1":6,"hpf_freq_0":50,"hpf_freq_1":50,"lpf_slope_0":48,"lpf_slope_1":48,"lpf_freq_0":23000,"lpf_freq_1":23000}}
 *
 * {"dev_name":"Speaker","ap_name":"PASS_FILTER","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"hpf_type":"null","lpf_type":"butterworth","ch_cnt":2,"hpf_slope_0":6,"hpf_slope_1":6,"hpf_freq_0":50,"hpf_freq_1":50,"lpf_slope_0":48,"lpf_slope_1":48,"lpf_freq_0":23000,"lpf_freq_1":23000}}
 */

/****** eq ******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"Speaker","ap_name":"EQ","ap_sub_id":1,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"eq"
 * must support channels and bin_num!!!
 * eg.
 * {"dev_name":"Speaker","ap_name":"EQ","ap_sub_id":1,"setup_mode":0,"param_type":"eq","param":{"BQ3":"1,3000,-1,0.6,1"}}
 *
 * {"dev_name":"Speaker","ap_name":"EQ","ap_sub_id":1,"setup_mode":0,"param_type":"eq","param":{"0_BQ2":"1,8000,1,0.6,1","1_BQ1":"1,500,1,0.6,1","1_BQ3":"1,1000,1,0.6,1"}}
 * KV3: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"EQ","ap_sub_id":1,"setup_mode":0,"param_type":"all","param":{"enable":1,"diff_param":0,"channels":2,"samplerate":48000,"bin_num":2,"BQ1":"1,500,1,0.6,1","BQ2":"1,1000,1,0.6,1"}}
 *
 * {"dev_name":"Speaker","ap_name":"EQ","ap_sub_id":1,"setup_mode":0,"param_type":"all","param":{"enable":1,"diff_param":1,"channels":2,"samplerate":48000,"0_bin_num":2,"0_BQ1":"1,500,1,0.6,1","0_BQ2":"1,1000,1,0.6,1","1_bin_num":3,"1_BQ1":"1,500,1,0.6,1","1_BQ2":"1,1000,1,0.6,1","1_BQ3":"1,1000,1,0.6,1"}}
 */

/****** rtc aec******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"MIC_PHONE_AEC","ap_name":"RTC_AEC","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"all"
 * eg.
 * {"dev_name":"MIC_PHONE_AEC","ap_name":"RTC_AEC","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"mode":"aggressive"}}
 * /

/****** rtc ans******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"MIC","ap_name":"RTC_ANS","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"RTC_ANS","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"mode":"Mild"}}
 * /

/****** rtc agc******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"MIC","ap_name":"RTC_AGC","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"RTC_AGC","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"mode":"unchanged","tgt_lv":3,"comp_gain":3,"limit":0,"level_min":0,"level_max":255}}
 * /

/****** surround ******
 * KV1: "param_type":"en"
 * eg.
 * {"dev_name":"Speaker","ap_name":"SURROUND","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
 *
 * KV2: "param_type":"all"
 * eg.
 * {"dev_name":"Speaker","ap_name":"SURROUND","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1}}
 * /

/****** inverter ******
* KV1: "param_type":"en"
* eg.
* {"dev_name":"Speaker","ap_name":"INVERTER","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
*
* KV2: "param_type":"all"
* eg.
* {"dev_name":"Speaker","ap_name":"INVERTER","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"ch_cnt":2,"ch0_i":0,"ch1_i":1}}
*/

/****** freq_domain_proc ******
* KV1: "param_type":"en"
* eg.
* {"dev_name":"Speaker","ap_name":"RP_FD_PROC","ap_sub_id":0,"setup_mode":0,"param_type":"en","param":{"enable":1}}
*
* KV2: "param_type":"all"
* eg.
* {"dev_name":"Speaker","ap_name":"RP_FD_PROC","ap_sub_id":0,"setup_mode":0,"param_type":"all","param":{"enable":1,"frame_cnt":4096}}
*/

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __SFX_PARAM_H */
