# BC03-R36S: A clock for the R36S

## Overview

Inspired by the Dieter Rams' Braun BC03 clock I look at when I'm working from
[Francesco's](https://nomnp.com) home.

## Inspiration

The core design ethos of this clock is a direct homage to the iconic Braun
BC03, a masterpiece of industrial design.

> Less, but better.

## Themes

The clock offers four unique colorways, each designed to evoke a specific mood while maintaining the iconic Braun yellow second hand:

*   **Stealth**: Dark walls, darker face, white/grey hands and ticks for a subtle, modern look.
*   **Classic**: Light walls, white face, black hands and ticks. The quintessential Braun aesthetic.
*   **Contrast**: Light walls, black face, white hands and ticks for a bold, clear display.
*   **Nightstand**: Dark walls, white face, black hands and ticks. Perfect for low-light environments.

## Build Instructions

This project uses `make` for building. It supports local compilation (for
development on your host machine) and cross-compilation for the R36S via a
container.

### Prerequisites

For local compilation. On macOS (Homebrew): `brew install sdl2`. On Linux
(Debian/Ubuntu): `sudo apt-get install libsdl2-dev`.
Docker or Podman (configured as `container` in `Makefile`) is required for R36S
cross-compilation.

### Local Build

To build the executable for your local machine:

```bash
make local
```
The executable will be named `bc03_local`.

### R36S Cross-Compilation

To build the executable for the R36S:

1.  Ensure you have a `Dockerfile` in the project root capable of building the `r36s-builder` image with `aarch64-linux-gnu-gcc` and SDL2 development libraries for the target architecture.
2.  Run the make command:

```bash
make r36s
```
This will build the container image (if not already built) and then cross-compile the project inside the container. The executable will be named `bc03_r36s`.

### Cleaning Build Artifacts

To remove all generated object files and executables:

```bash
make clean
```

## Usage

### Local Execution

After building locally, run the clock from your terminal:

```bash
./bc03_local
```

### R36S Execution

Transfer the `bc03_r36s` executable to your R36S device and run it. The exact
method depends on your R36S firmware and how you typically launch applications.

### Theme Cycling

While the clock is running:
*   Press the **Spacebar** on your keyboard.
*   Press **Button 0** on a connected gamepad.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## License

This project is licensed under the MIT License.
