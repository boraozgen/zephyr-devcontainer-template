FROM debian:bookworm-slim

ARG ZEPHYR_VERSION=v4.3.0
ARG ZEPHYR_SDK_TOOLCHAINS="arm-zephyr-eabi x86_64-zephyr-elf"

ENV ZEPHYR_BASE=/opt/zephyrproject/zephyr \
    ZEPHYR_TOOLCHAIN_VARIANT=zephyr \
    ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk \
    PATH=/opt/zephyr-venv/bin:${PATH}

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        cmake \
        file \
        git \
        gperf \
        ninja-build \
        python3-venv \
        wget \
        xz-utils \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/zephyr-venv \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir --upgrade pip west

RUN west init -m https://github.com/zephyrproject-rtos/zephyr --mr ${ZEPHYR_VERSION} /opt/zephyrproject \
    && cd /opt/zephyrproject \
    && west update --narrow -o=--depth=1 cmsis cmsis_6 hal_stm32 \
    && cd /opt/zephyrproject/zephyr \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir -r scripts/requirements-base.txt \
    && west sdk install --install-dir ${ZEPHYR_SDK_INSTALL_DIR} --toolchains ${ZEPHYR_SDK_TOOLCHAINS}

WORKDIR /workspaces