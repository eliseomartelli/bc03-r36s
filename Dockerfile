FROM debian:bullseye

RUN dpkg --add-architecture arm64

RUN apt-get update -y && \
    apt-get install -y --fix-missing \
    build-essential \
    crossbuild-essential-arm64 \
    libsdl2-dev:arm64 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Check SDL2 version by inspecting preprocessor defines
RUN aarch64-linux-gnu-gcc -dM -E -I/usr/include/SDL2 - < /dev/null | grep SDL_MAJOR_VERSION || true && \
    aarch64-linux-gnu-gcc -dM -E -I/usr/include/SDL2 - < /dev/null | grep SDL_MINOR_VERSION || true && \
    aarch64-linux-gnu-gcc -dM -E -I/usr/include/SDL2 - < /dev/null | grep SDL_PATCHLEVEL || true

CMD ["make", "r36s"]
