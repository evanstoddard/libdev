/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file spi_controller.h
 * @author Evan Stoddard
 * @brief SPI Controller Device Abstraction
 */

#ifndef LIBDEV_SPICONTROLLER_H
#define LIBDEV_SPICONTROLLER_H

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
 * @class spi_controller_api
 * @brief SPI Controller API
 *
 */
struct spi_controller_api {
  int (*transmit)(const struct device *dev, const void *buf, size_t len);
  int (*receive)(const struct device *dev, void *buf, size_t len);
  int (*transmit_receive)(const struct device *dev, const void *tx_buf,
                          size_t tx_len, void *rx_buf, size_t rx_len);
};

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

/**
 * @brief [TODO:description]
 *
 * @param dev [TODO:parameter]
 * @param buf [TODO:parameter]
 * @param len [TODO:parameter]
 * @return [TODO:return]
 */
static inline int spi_controller_transmit(const struct device *dev,
                                          const void *buf, size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct spi_controller_api *)dev->api)->transmit(dev, buf, len);
}

/**
 * @brief [TODO:description]
 *
 * @param dev [TODO:parameter]
 * @param buf [TODO:parameter]
 * @param len [TODO:parameter]
 * @return [TODO:return]
 */
static inline int spi_controller_receive(const struct device *dev, void *buf,
                                         size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct spi_controller_api *)dev->api)->receive(dev, buf, len);
}

/**
 * @brief [TODO:description]
 *
 * @param dev [TODO:parameter]
 * @param tx_buf [TODO:parameter]
 * @param tx_len [TODO:parameter]
 * @param rx_buf [TODO:parameter]
 * @param rx_len [TODO:parameter]
 * @return [TODO:return]
 */
static inline int spi_controller_transmit_receive(const struct device *dev,
                                                  const void *tx_buf,
                                                  size_t tx_len, void *rx_buf,
                                                  size_t rx_len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (tx_buf == NULL || tx_len == 0 || rx_buf == NULL || rx_len == 0) {
    return -EINVAL;
  }

  return ((struct spi_controller_api *)dev->api)
      ->transmit_receive(dev, tx_buf, tx_len, rx_buf, rx_len);
}

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_SPICONTROLLER_H */
