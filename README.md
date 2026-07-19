# libdev

`libdev` is a small C library that brings Zephyr-style driver and hardware
abstractions to non-Zephyr firmware: baremetal or FreeRTOS projects where
you don't have Zephyr's device model available.

## Motivation

Zephyr's driver model makes it easy to write hardware-agnostic code and
declare driver instances up front, then swap the underlying implementation
without touching the code that uses it. When working on baremetal or
FreeRTOS firmware, that abstraction is usually missing, and drivers end up
tightly coupled to a specific peripheral or vendor HAL.

`libdev` aims to bring that same shape, a common `struct device` handle, an
API vtable per subsystem, and generic accessor functions, to plain C
firmware, independent of any RTOS.

This project is in its very early stages.
