# Zephyr Evaluation Workspace

This workspace uses a VS Code development container to provide a repeatable Zephyr RTOS build environment.

## Why Debian

Debian Bookworm Slim works here and keeps the base image smaller than Ubuntu. Ubuntu was only the initial conservative choice because Zephyr's docs target Ubuntu package names directly. The required packages are also available on Debian, so the leaner base is a reasonable fit.

## What the container installs

- The latest stable Zephyr release at image build time
- Zephyr modules from the matching upstream manifest
- Python dependencies via `west packages pip --install`
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

## Notes

- Because the Zephyr version is resolved when the image is built and `west sdk install` selects a compatible SDK during image creation, rebuilding the container later can pick up newer stable releases.
- If you want stricter reproducibility later, replace the dynamic version resolution in `.devcontainer/Dockerfile` with explicit version pins.
