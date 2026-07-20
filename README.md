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

Unlike Zephyr, the declarative layer is intentionally loosely coupled from
the API layer. Instances are declared in a simple definition file, and a
small dependency-free generator turns that into the macros drivers consume.
Richer front ends (a bindings/properties system, or even devicetree) could
be added later without changing the driver or application-facing APIs.

## How it works

Device instances are declared in a `device.def` file, one entry per
instance, naming the instance and the driver compat that backs it:

```c
LIBDEV_DEVICE(flash0, STM32_INTERNAL_FLASH)
```

A small Python script (no dependencies) generates a per-compat foreach
macro from that file at build time. Drivers instantiate their devices
Zephyr-style: name your compat, provide a per-instance init macro, and
invoke the foreach:

```c
#define LIBDEV_DRV_COMPAT STM32_INTERNAL_FLASH

/* ... api implementation ... */

#define STM32_INTERNAL_FLASH_INIT(n)                                    \
  LIBDEV_DEVICE_DEFINE(n, &prv_api, NULL, NULL)

LIBDEV_INST_FOREACH(STM32_INTERNAL_FLASH_INIT)
```

Application code only ever sees the generic handle and the subsystem API:

```c
const struct device *flash = LIBDEV_DEVICE_GET(flash0);
flash_read(flash, 0, buf, sizeof(buf));
```

Integration is two CMake directives:

```cmake
add_subdirectory(path/to/libdev)
libdev_add_to_target(my_app DEF_FILE src/device.def)
```

Some properties of the design:

- Instances are `const`, bound at compile/link time, and live in rodata.
  There is no runtime registry, no boot-time registration walk, and no RAM
  cost for the device model itself.
- Vendor and HAL headers stay confined to each driver's own translation
  unit. Application code and other drivers never see them.
- Subsystem API calls are inlined shims that validate arguments and
  dispatch through the instance's vtable.

## Status

Very early. The core device model, `flash` and `i2cbus` subsystem APIs,
the generator, and the CMake integration are working end to end on an
STM32H5 test project. Per-instance configuration (passing values from
`device.def` into driver config structs) is not implemented yet. APIs are
unstable and subject to redesign.
