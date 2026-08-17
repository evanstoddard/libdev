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
 * @class i2cbus_target_config
 * @brief I2C target configuration definition
 *
 */
struct i2cbus_target_config {
  struct i2cbus_target_config *next;

  uint16_t addr;
  const struct i2cbus_target_callbacks *callbacks;

  const struct device *dev;
  uint8_t rx_byte;
  uint8_t tx_byte;
};

/**
 * @class i2cbus_target_callbacks
 * @brief I2C target callbacks
 *
 */
struct i2cbus_target_callbacks {
  int (*write_requested)(const struct device *device,
                         struct i2cbus_target_config *config);

  int (*write_received)(const struct device *device,
                        struct i2cbus_target_config *config, uint8_t val);

  int (*read_requested)(const struct device *device,
                        struct i2cbus_target_config *config, uint8_t *val);

  int (*read_processed)(const struct device *device,
                        struct i2cbus_target_config *config, uint8_t *val);

  int (*stop)(const struct device *device, struct i2cbus_target_config *config);
};

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
  int (*write_read)(const struct device *dev, const void *write_buf,
                    size_t write_len, void *read_buf, size_t read_len,
                    uint16_t addr, uint32_t timeout);
  int (*register_target)(const struct device *dev,
                         struct i2cbus_target_config *target_config);
  int (*unregister_target)(const struct device *dev,
                           struct i2cbus_target_config *target_config);
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

static inline int i2cbus_write_read(const struct device *dev,
                                    const void *write_buf, size_t write_len,
                                    void *read_buf, size_t read_len,
                                    uint16_t addr, uint32_t timeout) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (write_buf == NULL || read_buf == NULL || write_len == 0 ||
      read_len == 0) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)
      ->write_read(dev, write_buf, write_len, read_buf, read_len, addr,
                   timeout);
}

/**
 * @brief Register I2C target endpoint and enable target mode
 *
 * @param dev Pointer to device instance
 * @param target_config Pointer to target configuration
 * @retval -ENODEV Device instance is NULL
 * @retval -EINVAL Invalid input arguments
 * @retval 0 Success
 */
static inline int
i2cbus_register_target(const struct device *dev,
                       struct i2cbus_target_config *target_config) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (target_config == NULL) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)->register_target(dev, target_config);
}

/**
 * @brief Unregister I2C target endpoint
 *
 * @param dev Pointer to device instance
 * @param target_config Pointer to target configuration
 * @retval -ENODEV Device instance is NULL
 * @retval -EINVAL Invalid input arguments
 * @retval 0 Success
 */
static inline int
i2cbus_unregister_target(const struct device *dev,
                         struct i2cbus_target_config *target_config) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (target_config == NULL) {
    return -EINVAL;
  }

  return ((struct i2cbus_api *)dev->api)->unregister_target(dev, target_config);
}

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_I2CBUS_H */
