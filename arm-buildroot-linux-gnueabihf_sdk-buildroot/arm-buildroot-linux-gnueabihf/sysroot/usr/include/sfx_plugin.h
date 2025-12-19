/*
 * Copyright (c) 2024 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the people's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * sfx_mgmt.h -- sfx for plugin api
 *
 * dingbinyuan <dby@allwinnertech.com>
 */

#ifndef __SFX_PLUGIN_H
#define __SFX_PLUGIN_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <stdio.h>
#include <stdint.h>
#include "sfx_list.h"
#include "sfx_mgmt.h"

#define SECTION(x)  __attribute__((used,section(x)))

#define REGISTER_SFX_MGMT_AP(ap) \
    const struct sfx_plugin* sfx_mgmt_ap_##ap SECTION("sfx_mgmt_ap") = &(ap)

/****** rp plugin io ******/
typedef void rpsfx_io_t;

enum AP_DOMAIN {
    AP_DOMAIN_SYS = 0,
    AP_DOMAIN_DSP,
    AP_DOMAIN_DSP0,
    AP_DOMAIN_RV,
    AP_DOMAIN_CNT,
};

enum RPSFX_CMD {
    RPSFX_PLATIO_ADD_LINK = 1,
    RPSFX_PLATIO_DEL_LINK,
    RPSFX_SUBIO_CREATE,
    RPSFX_SUBIO_DESTROY,
    RPSFX_SUBIO_INIT,
    RPSFX_SUBIO_EXIT,
    RPSFX_AP_ID_CREATE,
    RPSFX_AP_ID_DESTROY,
    RPSFX_AP_ID_PROCESS,
    RPSFX_AP_ID_SETPARAM,
};

struct rpio_cfg {
    uint32_t payload_buffer_size;
};

struct rpio_attr {
    uint8_t *payload;
    uint32_t io_buffer_size;
};

/* WARNING: Must maintain 8-byte alignment */
struct rpsfx_data_head {
    uint8_t effect_id;
    enum RPSFX_CMD io_cmd;
    uint32_t payload_size_valid;
    int32_t ret;
};

struct rpsfx_data {
    struct rpsfx_data_head head;
    uint32_t payload_size;
    uint8_t *payload;
};

rpsfx_io_t *sfxmgmt_rpio_register(struct rpio_cfg *cfg);
void sfxmgmt_rpio_unregister(rpsfx_io_t *rpsfx_io);
int sfxmgmt_rpio_init(rpsfx_io_t *rp);
int sfxmgmt_rpio_exit(rpsfx_io_t *rp);
int sfxmgmt_rpio_send(rpsfx_io_t *rp, struct rpsfx_data *data);
int sfxmgmt_rpio_recv(rpsfx_io_t *rp, struct rpsfx_data *data);

void sfxmgmt_rpio_set_domain(rpsfx_io_t *rp, enum AP_DOMAIN domain);
void sfxmgmt_rpio_get_attr(rpsfx_io_t *rp, struct rpio_attr *attr);

/****** plugin adapter ******/
enum AP_MODE {
    AP_MODE_BYPASS = 0,
    AP_MODE_WORK,
};

enum AP_TYPE {
    AP_TYPE_HW = 0,
    AP_TYPE_SW,
    AP_TYPE_RP,
};

enum AP_STREAM {
    AP_STREAM_PLAYBACK = 0,
    AP_STREAM_CAPTURE,
};

enum AP_PROCESS_SIGN {
    AP_PROC_CYCLE = 0,
    AP_PROC_ONCE,
    AP_PROC_COMPLETE,
};

struct sfx_param_id {
    int dev_id;                 /* match sfx_plugin->dev_id */
    unsigned int ap_sub_id;     /* match sfx_plugin->ap_sub_id */
};

struct sfx_plugin {
    struct sfx_list_head list;
    const char *ap_name;
    unsigned int ap_sub_id;

    int (*ap_init)(struct sfx_plugin *ap);
    int (*ap_exit)(struct sfx_plugin *ap);
    int (*ap_process)(struct sfx_plugin *ap,
                      void *in_data, uint32_t in_size,
                      void **out_data, uint32_t *out_size);
    int (*ap_setup)(struct sfx_plugin *ap, void *param);
    int (*ap_updata_mode)(struct sfx_plugin *ap, enum AP_MODE mode);

    int (*ap_param_parser_all)(struct sfx_list_head *param_list, char *params_file);
    void (*ap_param_free_all)(struct sfx_list_head *param_list);
    int (*ap_param_parser_unit)(void **param, char *params_file, struct sfx_param_id *param_id);
    void (*ap_param_free_unit)(void *param);
    int (*ap_param_parser_cmd)(struct sfx_plugin *ap, void **param, char *key, void *ap_param);
    void (*ap_param_free_cmd)(struct sfx_plugin *ap, void *param);

    char *(*ap_get_version)(void);

    /* param config */
    void *priv;

    /* attribute config */
    const enum AP_TYPE type;
    const enum AP_DOMAIN domain;
    enum AP_STREAM stream;
    int dev_id;
    unsigned int param_set_method;
    const char *param_file;             /* will change if custom in config file */
    struct sfx_list_head *param_list;

    /* remoute proccess io */
    rpsfx_io_t *rpsfx_io;
    uint8_t rpsfx_pool_id;

    /* runtime config */
    int dev_running;
    enum AP_MODE mode;
    enum AP_PROCESS_SIGN proc_sign;
    struct sfx_pcm_config inpcm_config;
    struct sfx_pcm_config outpcm_config;
    unsigned int frames;

    /* debug info */
    unsigned int dump_last_num;
    unsigned int dump_data_cnt;
    char *dump_file_name;
    FILE *dump_file;
    uint32_t dump_buf_len;
    int8_t *dump_buf;
};

/****** commonly used functions ******/
#define SFX_ALIGN_8B(x)             \
    do {                            \
        x = (((x) + (7)) & ~(7));   \
    } while(0)

#define sfx_free(__ptr) {   \
        if (__ptr) {        \
            free(__ptr);    \
            __ptr = NULL;   \
        }                   \
    }

/* pcm data convert */
int sfxmgmt_interleaved_to_plane(void *i_data, uint32_t size, void *p_data,
                                 struct sfx_pcm_config pcm_config, unsigned int frames);
int sfxmgmt_plane_to_interleaved(void *p_data, uint32_t size, void *i_data,
                                 struct sfx_pcm_config pcm_config, unsigned int frames);

/* param match */
struct sfx_reg_dev {
    struct sfx_devid *devid;
    uint8_t devid_cnt;
};

struct sfx_devid {
    int dev_id;
    char *dev_name;
};

int sfxmgmt_reg_dev_get(struct sfx_reg_dev **reg_dev);
int sfxmgmt_param_match_id(struct sfx_param_id *id, struct sfx_param_id *param_id);
int sfxmgmt_param_match_ap(struct sfx_plugin *ap, struct sfx_param_id *param_id);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __SFX_PLUGIN_H */
