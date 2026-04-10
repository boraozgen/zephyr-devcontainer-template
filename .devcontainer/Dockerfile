FROM debian:stable-slim

ARG ZEPHYR_VERSION=v4.3.0
ARG ZEPHYR_SDK_TOOLCHAINS="arm-zephyr-eabi x86_64-zephyr-elf"

ENV ZEPHYR_BASE=/opt/zephyrproject/zephyr \
    ZEPHYR_TOOLCHAIN_VARIANT=zephyr \
    ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains/zephyr-sdk \
    PATH=/opt/zephyr-venv/bin:${PATH}

RUN apt-get update \
    && apt-get install --yes --no-install-recommends \
        ca-certificates \
        ccache \
        cmake \
        file \
        g++-multilib \
        gcc-multilib \
        git \
        gperf \
        make \
        ninja-build \
        python3-venv \
        wget \
        xz-utils \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/zephyr-venv \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir --upgrade pip west

RUN west init \
        --manifest-url https://github.com/zephyrproject-rtos/zephyr \
        --manifest-rev ${ZEPHYR_VERSION} \
        --clone-opt=--depth=1 \
        /opt/zephyrproject \
    && cd /opt/zephyrproject \
    && west update --narrow --fetch-opt=--depth=1 cmsis cmsis_6 hal_stm32 hal_nordic segger \
    && cd /opt/zephyrproject/zephyr \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir --requirement scripts/requirements-base.txt \
    && west sdk install --install-dir ${ZEPHYR_SDK_INSTALL_DIR} --toolchains ${ZEPHYR_SDK_TOOLCHAINS}

WORKDIR /workspaces