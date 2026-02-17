FROM debian:bookworm

RUN dpkg --add-architecture arm64

RUN apt-get update -y && \
    apt-get install -y --fix-missing \
    build-essential \
    crossbuild-essential-arm64 \
    libsdl2-dev:arm64 \
    libasound2-dev:arm64 \
    libpulse-dev:arm64 \
    libx11-dev:arm64 \
    libxext-dev:arm64 \
    libxcursor-dev:arm64 \
    libxi-dev:arm64 \
    libxfixes-dev:arm64 \
    libxrandr-dev:arm64 \
    libxss-dev:arm64 \
    libdrm-dev:arm64 \
    libgbm-dev:arm64 \
    libwayland-dev:arm64 \
    libxkbcommon-dev:arm64 \
    libdecor-0-dev:arm64 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

CMD ["make", "r36s"]
