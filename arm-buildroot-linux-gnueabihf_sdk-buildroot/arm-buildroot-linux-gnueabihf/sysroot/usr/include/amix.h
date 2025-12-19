/*
 * Copyright (c) 2024 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 * the the people's Republic of China and other countries.
 * All Allwinner Technology Co.,Ltd. trademarks are used with permission.
 *
 * amix.h -- audio mix api
 *
 * dingbinyuan <dby@allwinnertech.com>
 */

#ifndef __AUDIO_SYSTEM_H
#define __AUDIO_SYSTEM_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef void amix_t;
typedef void amix_dev_t;

struct amix_pcm_config {
    uint32_t channels;
    uint32_t rate;
    uint32_t bit;
    uint32_t period_size;
    uint32_t period_count;
};

struct amix_stream {
    int (*open_stream)(struct amix_stream *stream, struct amix_pcm_config *pcm_cfg);
    int (*close_stream)(struct amix_stream *stream);
    int (*do_stream)(struct amix_stream *stream, void *data, uint32_t size,
                     void **data_out, uint32_t *data_out_size);
    int (*write)(struct amix_stream *stream, void *buf, uint32_t size);

    char dev_name[32];
    struct amix_pcm_config pcm_cfg;
    void *handle;
};

/****** Basic api: amix ******/
/* only for server */
int amix_init(amix_t **amix);
void amix_exit(amix_t *amix);
int amix_dev_register(amix_t *amix, struct amix_stream *stream);
int amix_dev_unregister(amix_t *amix, const char *dev_name);

/* only for client */
amix_dev_t *amix_dev_open(const char *dev_name, struct amix_pcm_config *pcm_cfg);
int amix_dev_close(amix_dev_t *adev);
int amix_dev_do(amix_dev_t *adev, void *data, uint32_t size,
                void **data_out, uint32_t *data_out_size);
int amix_dev_write(amix_dev_t *adev, void *buf, uint32_t size);

/****** Basic api: misc ******/
void amix_show_version(amix_t *amix);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __AUDIO_SYSTEM_H */
