# Zephyr Evaluation Workspace

This workspace uses a VS Code development container to provide a repeatable Zephyr RTOS build environment.

## Why Debian

Debian Stable Slim keeps the base image small while still tracking Debian's current stable release. Ubuntu was only the initial conservative choice because Zephyr's docs target Ubuntu package names directly. The required packages are also available on Debian, so the leaner base is a reasonable fit.

## What the container installs

- Zephyr 4.3.0
- Only the Zephyr modules needed for the documented `qemu_x86_64` and `nucleo_f446re` builds: `cmsis`, `cmsis_6`, and `hal_stm32`
- A shallow manifest clone via `west init --clone-opt=--depth=1`
- Zephyr's base Python build requirements from `scripts/requirements-base.txt`
- A Zephyr-compatible SDK via `west sdk install`
- Default SDK toolchains: `arm-zephyr-eabi` and `x86_64-zephyr-elf`

The Zephyr sources live inside the container at `/opt/zephyrproject/zephyr`.

## Prerequisites

- Docker Desktop
- VS Code
- Dev Containers extension

## Open the workspace in the container

1. Open `c:\Users\oezgen.NANTIS\Desktop\zephyr-evaluation` in VS Code.
2. Run `Dev Containers: Reopen in Container`.
3. Wait for the image build and container startup to finish.

## Build inside the container

From a terminal inside the container, build the app for a host smoke-test target:

```sh
west build -p always -b qemu_x86_64 . -d build/qemu_x86_64
```

Build the same app for a representative STM32 target:

```sh
west build -p always -b nucleo_f446re . -d build/nucleo_f446re
```

You can switch boards by replacing `nucleo_f446re` with any board supported by the installed SDK toolchains.

## VS Code task

Use the `Build Zephyr app` task and enter the board name when prompted.

## VS Code CMake Tools

The workspace now includes CMake presets so the CMake Tools extension can drive Zephyr builds directly.

1. Run `CMake: Select Configure Preset` and choose one of the Zephyr board presets:
   - `qemu_x86_64`
   - `nucleo_f446re`
   - `nucleo_h755zi_q`
2. Run `CMake: Configure`.
3. Run `CMake: Build`.

The selected preset controls the Zephyr `BOARD` value and sends output to a matching build directory under `build/`.

After configuration, `CMake: Select Build Target` can be used to switch between generated Zephyr targets such as the default app build and any extra targets exposed by Zephyr for the selected board.

## Notes

- The Dockerfile pins Zephyr to `v4.3.0`.
- The SDK version is selected by `west sdk install` from Zephyr's `SDK_VERSION` file for that pinned release.
