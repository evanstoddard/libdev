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

#ifdef __cplusplus
}
#endif
#endif /* LIBDEV_DEVICE_H */
