/*
 * Copyright (C) Evan Stoddard
 */

/**
 * @file led_strip.h
 * @author Evan Stoddard
 * @brief LED Strip abstraction
 */

#ifndef led_strip_h
#define led_strip_h

#include <errno.h>
#include <stddef.h>
#include <stdint.h>

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

struct led_rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct led_strip_api {
  int (*update_rgb)(const struct device *dev, size_t start_idx,
                    struct led_rgb *rgb_buf, size_t num_leds);
  int (*stage_update_rgb)(const struct device *dev, size_t start_idx,
                          struct led_rgb *rgb_buf, size_t num_leds);

  int (*set_all)(const struct device *dev, struct led_rgb *rgb);
  int (*clear)(const struct device *dev);
  int (*num_leds)(const struct device *dev, size_t *num_leds);
  int (*commit)(const struct device *dev);
};

/*****************************************************************************
 * Function Prototypes
 *****************************************************************************/

static inline int led_strip_update_rgb(const struct device *dev,
                                       size_t start_idx,
                                       struct led_rgb *rgb_buf,
                                       size_t num_leds) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (rgb_buf == NULL) {
    return -EINVAL;
  }

  return ((struct led_strip_api *)dev->api)
      ->update_rgb(dev, start_idx, rgb_buf, num_leds);
}

static inline int led_strip_stage_update_rgb(const struct device *dev,
                                             size_t start_idx,
                                             struct led_rgb *rgb_buf,
                                             size_t num_leds) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (rgb_buf == NULL) {
    return -EINVAL;
  }

  return ((struct led_strip_api *)dev->api)
      ->stage_update_rgb(dev, start_idx, rgb_buf, num_leds);
}

static inline int led_strip_set_all(const struct device *dev,
                                    struct led_rgb *rgb) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (rgb == NULL) {
    return -EINVAL;
  }

  return ((struct led_strip_api *)dev->api)->set_all(dev, rgb);
}

static inline int led_strip_clear(const struct device *dev) {
  if (dev == NULL) {
    return -ENODEV;
  }

  return ((struct led_strip_api *)dev->api)->clear(dev);
}

static inline int led_strip_num_leds(const struct device *dev,
                                     size_t *num_leds) {
  if (dev == NULL) {
    return -ENODEV;
  }

  if (num_leds == NULL) {
    return -EINVAL;
  }

  return ((struct led_strip_api *)dev->api)->num_leds(dev, num_leds);
}

static inline int led_strip_commit(const struct device *dev) {
  if (dev == NULL) {
    return -ENODEV;
  }

  return ((struct led_strip_api *)dev->api)->commit(dev);
}

#ifdef __cplusplus
}
#endif
#endif /* led_strip_h */
