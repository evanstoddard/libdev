/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file device.h
 * @author Evan Stoddard
 * @brief
 */

#ifndef LIBDEV_DEVICE_H
#define LIBDEV_DEVICE_H

#include "device_priv.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

/**
 * @typedef device
 * @brief Device instance
 *
 */
struct device {
  void *config;
  void *data;
  void *api;
};

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#define LIBDEV_DEVICE_ATTR(name, key, val)

/* Expand the project's device.def once, emitting an extern for every
 * instance. LIBDEV_DEVICE is redefined to nothing afterward so any later
 * expansion of a def entry in this translation unit is a no-op. */
#define LIBDEV_DEVICE(name, compat, base_addr, parent_dev)                     \
  extern const struct device LIBDEV_DEV_INST_NAME(name);
#include LIBDEV_DEFINITION_INCLUDE
#undef LIBDEV_DEVICE
#define LIBDEV_DEVICE(name, compat)

/* Generated LIBDEV_FOREACH_<compat>(fn) macros, one per compat in
 * device.def. Pure macro definitions, safe to include unconditionally. */
#include "device_instances.inc"

/**
 * @def LIBDEV_DEVICE_DEFINE
 * @brief Defines the struct device instance for a device.def entry
 *
 * Invoked from a driver's per-instance init macro (via
 * LIBDEV_INST_FOREACH), analogous to Zephyr's DEVICE_DT_INST_DEFINE.
 */
#define LIBDEV_DEVICE_DEFINE(name, _api, _config, _data)                       \
  const struct device LIBDEV_DEV_INST_NAME(name) = {                           \
      .config = (_config), .data = (_data), .api = (_api)};

/**
 * @def LIBDEV_INST_FOREACH
 * @brief Invokes fn(name) for every device.def instance of the driver's
 *        compat
 *
 * The driver must define LIBDEV_DRV_COMPAT (its compat token) before
 * invoking this, analogous to Zephyr's DT_DRV_COMPAT +
 * DT_INST_FOREACH_STATUS_OKAY(fn).
 */
#define LIBDEV_INST_FOREACH(fn)                                                \
  LIBDEV_CONCAT(LIBDEV_FOREACH_, LIBDEV_DRV_COMPAT)(fn)

/**
 * @def LIBDEV_DEVICE_GET
 * @brief Retrieves the struct device pointer for a device instance by name
 */
#define LIBDEV_DEVICE_GET(inst_name) (&LIBDEV_DEV_INST_NAME(inst_name))

#define LIBDEV_DEVICE_GET_BASE_ADDR(inst_name)                                 \
  (&(LIBDEV_DEVICE_##inst_name##_BASE_ADDR))

#define LIBDEV_DEVICE_GET_PARENT_DEV_INST(inst_name)                           \
  LIBDEV_DEVICE_GET(LIBDEV_DEVICE_##inst_name##_PARENT_DEV)

#define LIBDEV_DEVICE_GET_ATTR(inst_name, key)                                 \
  (LIBDEV_DEVICE_INST_##inst_name##_ATTR_##key)

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_DEVICE_H */
