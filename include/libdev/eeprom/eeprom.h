/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file eeprom.h
 * @author Evan Stoddard
 * @brief
 */

#ifndef LIBDEV_EEPROM_H
#define LIBDEV_EEPROM_H

#include <libdev/device.h>

#include <errno.h>
#include <stddef.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Definitions
 *****************************************************************************/

/*****************************************************************************
 * Structs, Unions, Enums, & Typedefs
 *****************************************************************************/

struct eeprom_api {
  int (*read)(const struct device *dev, off_t offset, void *buf, size_t len);
  int (*write)(const struct device *dev, off_t offset, const void *buf,
               size_t len);
};

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

static inline int eeprom_read(const struct device *dev, off_t offset, void *buf,
                              size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct eeprom_api *)dev->api)->read(dev, offset, buf, len);
}

static inline int eeprom_write(const struct device *dev, off_t offset,
                               const void *buf, size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct eeprom_api *)dev->api)->write(dev, offset, buf, len);
}

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_EEPROM_H */
