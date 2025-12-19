/*
 * Copyright (c) 2024 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the people's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * sfx_mgmt.h -- sfx for mgmt api
 *
 * dingbinyuan <dby@allwinnertech.com>
 */

#ifndef __SFX_MGMT_H
#define __SFX_MGMT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define SFX_MGMT_AUDIO_DEVICE_DESC sfxmgmt_get_desc_path()

typedef void sfxmgmt_t;
typedef void sfxdev_t;

enum sfx_pcm_format {
    SFX_PCM_FORMAT_INVALID = -1,
    SFX_PCM_FORMAT_S16_LE = 0,  /* 16-bit signed */
    SFX_PCM_FORMAT_S32_LE,      /* 32-bit signed */
    SFX_PCM_FORMAT_S8,          /* 8-bit signed */
    SFX_PCM_FORMAT_S24_LE,      /* 24-bits in 4-bytes */
    SFX_PCM_FORMAT_S24_3LE,     /* 24-bits in 3-bytes */

    SFX_PCM_FORMAT_MAX,
};

enum sfx_pcm_data_mode {
    SFX_PCM_DATA_I = 0,
    SFX_PCM_DATA_N,
};

typedef struct sfx_pcm_config {
    uint32_t channels;
    uint32_t rate;
    uint32_t bit;
    enum sfx_pcm_format format;
    uint32_t period_size;
    uint32_t period_count;

    enum sfx_pcm_data_mode data_mode;
} sfx_pcm_cfg_t;

/* Basic api: sfxmgmt */
char *sfxmgmt_get_desc_path();
int sfxmgmt_init(sfxmgmt_t **sfxmgmt, char *desc_file);
void sfxmgmt_exit(sfxmgmt_t *sfxmgmt);

/* Basic api: pcm stream */
sfxdev_t *sfxmgmt_ap_open(sfxmgmt_t *sfxmgmt, const char *dev_name, sfx_pcm_cfg_t *pcm_cfg);
int sfxmgmt_ap_close(sfxdev_t *sfxdev);
int sfxmgmt_ap_do(sfxdev_t *sfxdev,
                  void *in, uint32_t in_size,
                  void **out, uint32_t *out_size);

/* Basic api: parm setup */
int sfxmgmt_parm_adjust_server(sfxmgmt_t *sfxmgmt);
void sfxmgmt_parm_adjust_destroy(sfxmgmt_t *sfxmgmt);
int sfxmgmt_parm_setup_byfile(sfxmgmt_t *sfxmgmt, char *dev_name,
                              char *ap_name, char *ap_sub_id, char *parm_file_path);

/* Basic api: cmd parm setup */
int sfxmgmt_parm_setup_cache(sfxmgmt_t *sfxmgmt, char *val);
int sfxmgmt_parm_setup_done(sfxmgmt_t *sfxmgmt, char *val);
int sfxmgmt_parm_setup_sync(sfxmgmt_t *sfxmgmt, char *val);
int sfxmgmt_parm_setup(sfxmgmt_t *sfxmgmt, char *val);

/* Basic api: misc */
void sfxmgmt_show_version(sfxmgmt_t *sfxmgmt);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __SFX_MGMT_H */
