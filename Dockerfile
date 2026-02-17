FROM debian:bullseye

RUN dpkg --add-architecture arm64

RUN apt-get update && apt-get install -y \
    build-essential \
    crossbuild-essential-arm64 \
    libsdl2-dev:arm64 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

CMD ["make", "r36s"]
