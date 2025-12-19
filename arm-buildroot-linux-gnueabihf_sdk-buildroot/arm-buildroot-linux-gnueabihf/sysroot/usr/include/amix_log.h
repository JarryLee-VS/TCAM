/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * amix_log.h -- amix for log api
 *
 * Dby <dby@allwinnertech.com>
 *
 * Copyright (c) 2024 Allwinnertech Ltd.
 */

#ifndef __AMIX_LOG_H
#define __AMIX_LOG_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/* menuconfig->Platform Selection->Print set->Open debug print */
#define CONFIG_ASMGMT_PRINT_DEBUG_ON
#ifdef CONFIG_ASMGMT_PRINT_DEBUG_ON
#define AMIX_LOG_DEBUG    1
#else
#define AMIX_LOG_DEBUG    0
#endif

/* menuconfig->Platform Selection->Print set->Unify print to terminal */
#define CONFIG_ASMGMT_PRINT_TO_TERMINAL
#ifdef CONFIG_ASMGMT_PRINT_TO_TERMINAL
/* unify print to terminal. */
#if AMIX_LOG_DEBUG


#define AMIX_DLOG(method, mark, format, ...) \
    method(mark ": " format, ##__VA_ARGS__)

#define aloge(format, ...) AMIX_DLOG(error, "<E> ", format, ##__VA_ARGS__)
#define alogd(format, ...) AMIX_DLOG(debug, "<D> ", format, ##__VA_ARGS__)
#define alogw(format, ...) AMIX_DLOG(warn, "<W> ", format, ##__VA_ARGS__)
#define alogi(format, ...) AMIX_DLOG(info, "<I> ", format, ##__VA_ARGS__)
#define alogv(format, ...) AMIX_DLOG(verbose, "<V> ", format, ##__VA_ARGS__)

void error(const char *format, ...);
void warn(const char *format, ...);
void info(const char *format, ...);
void debug(const char *format, ...);
void verbose(const char *format, ...);

#define amix_log_debug(fmt, args...) \
    alogd("[%s %d] " fmt, __func__, __LINE__, ##args)
#else
#define amix_log_debug(fmt, args...) \
    do {                            \
        if (false)                  \
            printf(fmt, ##args);    \
    } while (false)
#endif

#define amix_log_info(fmt, args...)  \
    alogi("[%s %d] " fmt, __func__, __LINE__, ##args)

#define amix_log_warn(fmt, args...)  \
    alogw("[%s %d] " fmt, __func__, __LINE__, ##args)

#define amix_log_err(fmt, args...)   \
    aloge("[%s %d] " fmt, __func__, __LINE__, ##args)

#define amix_log_show(fmt, args...)  \
    printf(fmt, ##args)

#else
/* print to logcat when target is android and not defined ASMGMT_PRINT_TO_TERMINAL. */
#ifdef CONFIG_AMIX_TARGET_ANDROID
#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "AS"
#endif

#if AMIX_LOG_DEBUG
#define amix_log_debug(fmt, args...) \
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[DBG][%s %d] " fmt, __func__, __LINE__, ##args);
#else
#define amix_log_debug(fmt, args...) \
    do {                            \
        if (false)                  \
            printf(fmt, ##args);    \
    } while (false)
#endif

#define amix_log_info(fmt, args...)  \
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[INF][%s %d] " fmt, __func__, __LINE__, ##args);

#define amix_log_warn(fmt, args...)  \
        __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "[WARN][%s %d] " fmt, __func__, __LINE__, ##args);

#define amix_log_err(fmt, args...)   \
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[ERR][%s %d] " fmt, __func__, __LINE__, ##args);

#define amix_log_show(fmt, args...)  \
        __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,  fmt, ##args);

#else
/* Default printing. */
#if AMIX_LOG_DEBUG
#define amix_log_debug(fmt, args...) \
    printf("[DBG][%s %d] \n" fmt, __func__, __LINE__, ##args)
#else
#define amix_log_debug(fmt, args...) \
    do {                            \
        if (false)                  \
            printf(fmt, ##args);    \
    } while (false)
#endif

#define amix_log_info(fmt, args...)  \
    printf("[INF][%s %d] \n" fmt, __func__, __LINE__, ##args)

#define amix_log_warn(fmt, args...)  \
    printf("[WARN][%s %d] \n" fmt, __func__, __LINE__, ##args)

#define amix_log_err(fmt, args...)   \
    printf("[ERR][%s %d] \n" fmt, __func__, __LINE__, ##args)

#define amix_log_show(fmt, args...)  \
    printf(fmt, ##args)
#endif
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __AMIX_LOG_H */
