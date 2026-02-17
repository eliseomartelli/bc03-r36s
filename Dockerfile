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

CMD ["make", "r36s"]
