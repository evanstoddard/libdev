/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file flash.h
 * @author Evan Stoddard
 * @brief Flash abstraction
 */

#ifndef LIBDEV_FLASH_H
#define LIBDEV_FLASH_H

#include <errno.h>

#include <stddef.h>
#include <stdint.h>

#include <unistd.h>

#include <libdev/device.h>

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
 * @class flash_api
 * @brief Flash API definition
 *
 */
struct flash_api {
  int (*read)(struct device *dev, off_t offset, void *buf, size_t len);
  int (*write)(struct device *dev, off_t offset, const void *buf, size_t len);
  int (*write_align_size)(struct device *dev, size_t *write_align_size);
  int (*size)(struct device *dev, size_t *size);
  int (*num_sectors)(struct device *dev, uint32_t *num_sectors);
  int (*sector_size)(struct device *dev, size_t *sector_size);
  int (*erase_val)(struct device *dev, uint8_t *erase_val);
};

/*****************************************************************************
 * Inline Functions
 *****************************************************************************/

static inline int flash_read(struct device *dev, off_t offset, void *buf,
                             size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->read(dev, offset, buf, len);
}

static inline int flash_write(struct device *dev, off_t offset, const void *buf,
                              size_t len) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (buf == NULL || len == 0) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->write(dev, offset, buf, len);
}

static inline int flash_write_align_size(struct device *dev,
                                         size_t *write_align_size) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (write_align_size == NULL) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)
      ->write_align_size(dev, write_align_size);
}

static inline int flash_size(struct device *dev, size_t *size) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (size == NULL) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->size(dev, size);
}

static inline int flash_num_sectors(struct device *dev, uint32_t *num_sectors) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (num_sectors == NULL) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->num_sectors(dev, num_sectors);
}

static inline int flash_sector_size(struct device *dev, size_t *sector_size) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (sector_size == NULL) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->sector_size(dev, sector_size);
}

static inline int flash_erase_val(struct device *dev, uint8_t *erase_val) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (erase_val == NULL) {
    return -EINVAL;
  }

  return ((struct flash_api *)dev->api)->erase_val(dev, erase_val);
}

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_FLASH_H */
