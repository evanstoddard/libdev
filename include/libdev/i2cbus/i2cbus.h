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

/**
 * @brief Shim to calling device instance's read API call
 *
 * @param device Pointer to device instance
 * @param Pointer to buffer to write read data into
 * @param Length of read
 * @param I2C address
 * @param Timeout for blocking read
 * @retval -ENODEV Device instance is NULL
 * @retval -EINVAL Invalid input arguments
 * @retval 0 Success
 */
static inline int i2cbus_read(const struct device *dev, void *buf, size_t len,
                              uint16_t addr, uint32_t timeout) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)->read(dev, buf, len, addr, timeout);
}

/**
 * @brief Shim to calling device instance's write API call
 *
 * @param device Pointer to device instance
 * @param Pointer to buffer to write
 * @param Length of bufer
 * @param I2C address
 * @param Timeout for blocking write
 * @retval -ENODEV Device instance is NULL
 * @retval -EINVAL Invalid input arguments
 * @retval 0 Success
 */
static inline int i2cbus_read(const struct device *dev, void *buf, size_t len,
                              uint16_t addr, uint32_t timeout) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)->read(dev, buf, len, addr, timeout);
}
static inline int i2cbus_write(const struct device *dev, const void *buf,
                               size_t len, uint16_t addr, uint32_t timeout) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)->write(dev, buf, len, addr, timeout);
}

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_I2CBUS_H */
