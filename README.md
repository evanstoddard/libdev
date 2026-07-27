# libdev

`libdev` is a small C library that brings Zephyr-style driver and hardware
abstractions to non-Zephyr firmware (e.g. Bare-metal, FreeRTOS, etc).

## Motivation

Zephyr's driver model makes it easy to write hardware-agnostic code and
declare driver instances up front, then swap the underlying implementation
without touching the code that uses it. When working on baremetal or
FreeRTOS firmware, that abstraction is usually missing, and drivers end up
tightly coupled to a specific peripheral or vendor HAL.

`libdev` aims to bring that same shape, a common `struct device` handle, an
API vtable per subsystem, and generic accessor functions, to plain C
firmware, independent of any RTOS.

Unlike Zephyr, the declarative layer is intentionally loosely coupled from
the API layer. Instances are declared in a simple definition file, and a
small dependency-free generator turns that into the macros drivers consume.
Richer front ends (a bindings/properties system, or even devicetree) could
be added later without changing the driver or application-facing APIs.

That being said, the intermediate layer is designed in such a way that one could create their own declaration file format, including device trees.

## Status

This project is very early in the development stage.  APIs are not stable and there are bound to be bugs.
