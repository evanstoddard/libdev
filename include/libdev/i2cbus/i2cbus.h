/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file i2cbus.h
 * @author Evan Stoddard
 * @brief I2C Bus abstraction
 */

#ifndef LIBDEV_I2CBUS_H
#define LIBDEV_I2CBUS_H

#include <libdev/device.h>

#include <errno.h>

#include <stddef.h>
#include <stdint.h>

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
 * @class i2cbus_api
 * @brief I2C Bus abstraction API
 *
 */
struct i2cbus_api {
  int (*read)(const struct device *dev, void *buf, size_t len, uint16_t addr,
              uint32_t timeout);
  int (*write)(const struct device *dev, const void *buf, size_t len,
               uint16_t addr, uint32_t timeout);
};

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

static inline int i2cbus_read(const struct device *dev, void *buf, size_t len,
                              uint16_t addr, uint32_t timeout) {
  return -ENOTSUP;
}

static inline int i2cbus_write(const struct device *dev, const void *buf,
                               size_t len, uint16_t addr, uint32_t timeout) {
  return -ENOTSUP;
}

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_I2CBUS_H */
