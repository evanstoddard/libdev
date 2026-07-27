/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file device_priv.h
 * @author Evan Stoddard
 * @brief Defines macros used internally to libdev
 */

#ifndef device_priv_h
#define device_priv_h

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/**
 * @brief Prefix for all generated defines, macros, and device instance structs
 */
#define LIBDEV_INST_PREFIX libdev_dev_inst_

#define LIBDEV_CONCAT_(a, b) a##b
#define LIBDEV_CONCAT(a, b) LIBDEV_CONCAT_(a, b)

/**
 * @brief Converts user specified device instance name to long form generated
 * name
 */
#define LIBDEV_DEV_INST_NAME(inst_name)                                        \
  LIBDEV_CONCAT(LIBDEV_INST_PREFIX, inst_name)

#ifdef __cplusplus
}
#endif
#endif /* device_priv_h */
