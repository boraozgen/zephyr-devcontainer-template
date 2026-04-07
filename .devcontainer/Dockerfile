FROM debian:bookworm-slim

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ARG DEBIAN_FRONTEND=noninteractive
ARG ZEPHYR_SDK_TOOLCHAINS="arm-zephyr-eabi x86_64-zephyr-elf"

ENV LANG=C.UTF-8 \
    LC_ALL=C.UTF-8 \
    ZEPHYR_BASE=/opt/zephyrproject/zephyr \
    ZEPHYR_TOOLCHAIN_VARIANT=zephyr \
    ZEPHYR_SDK_INSTALL_DIR=/opt/toolchains \
    PATH=/opt/zephyr-venv/bin:${PATH}

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        bash \
        ca-certificates \
        ccache \
        cmake \
        curl \
        device-tree-compiler \
        dfu-util \
        file \
        g++-multilib \
        gcc-multilib \
        git \
        gperf \
        jq \
        libmagic1 \
        libsdl2-dev \
        make \
        ninja-build \
        python3-dev \
        python3-pip \
        python3-setuptools \
        python3-venv \
        python3-wheel \
        wget \
        xz-utils \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m venv /opt/zephyr-venv \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir --upgrade pip \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir west

RUN set -eux; \
    ZEPHYR_TAG="$(git ls-remote --tags --refs https://github.com/zephyrproject-rtos/zephyr | awk -F/ '/refs\/tags\/v[0-9]+\.[0-9]+\.[0-9]+$/ { print $3 }' | sort -V | tail -n1)"; \
    test -n "${ZEPHYR_TAG}"; \
    west init -m https://github.com/zephyrproject-rtos/zephyr --mr "${ZEPHYR_TAG}" /opt/zephyrproject; \
    cd /opt/zephyrproject; \
    west update; \
    cd /opt/zephyrproject/zephyr; \
    west packages pip --install; \
    west sdk install --toolchains ${ZEPHYR_SDK_TOOLCHAINS}; \
    SDK_DIR="$(find /root /opt -maxdepth 2 -type d -name 'zephyr-sdk-*' | sort -V | tail -n1)"; \
    test -n "${SDK_DIR}"; \
    mkdir -p /opt/toolchains; \
    ln -s "${SDK_DIR}" "/opt/toolchains/$(basename "${SDK_DIR}")"

WORKDIR /workspaces