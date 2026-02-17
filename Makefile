TARGET          = bc03
SOURCES         = main.c theme.c geometry.c renderer.c
EXECUTABLE_R36S = $(TARGET)_r36s
EXECUTABLE_LOCAL= $(TARGET)_local

CC_LOCAL        = gcc
CFLAGS_LOCAL    = $(shell sdl2-config --cflags) -I. -O2 -Wall -MMD -MP
LIBS_LOCAL      = $(shell sdl2-config --libs) -lm
OBJECTS_LOCAL   = $(patsubst %.c,%.local.o,$(SOURCES))

RUNTIME         = container
IMG_NAME        = r36s-builder
CC_R36S_CONTAINER= aarch64-linux-gnu-gcc # Compiler inside the Docker container
CFLAGS_R36S_CONTAINER= -I/usr/include/SDL2 -I. -D_REENTRANT -O2 -Wall
LIBS_R36S_CONTAINER  = -lSDL2 -lm

.PHONY: all image r36s r36s-static local clean

all: local

local: $(EXECUTABLE_LOCAL)
	@echo "Successfully built $(EXECUTABLE_LOCAL) locally."

$(EXECUTABLE_LOCAL): $(OBJECTS_LOCAL)
	@echo "Linking locally..."
	$(CC_LOCAL) $(OBJECTS_LOCAL) -o $@ $(LIBS_LOCAL)

%.local.o: %.c
	@echo "Compiling for local: $<..."
	$(CC_LOCAL) $(CFLAGS_LOCAL) -c $< -o $@

image:
	@echo "Building Container Image ($(IMG_NAME))..."
	$(RUNTIME) build -t $(IMG_NAME) .

r36s: image
	@echo "Cross-Compiling for R36S inside Docker container..."
	$(RUNTIME) run --rm -v "$(PWD):/app" -w /app $(IMG_NAME) \
	$(CC_R36S_CONTAINER) -o $(EXECUTABLE_R36S) $(SOURCES) $(CFLAGS_R36S_CONTAINER) $(LIBS_R36S_CONTAINER)
	@echo "Successfully built $(EXECUTABLE_R36S) for R36S."
	@echo "Transfer '$(EXECUTABLE_R36S)' to your device."

r36s-static: image
	@echo "Cross-Compiling for R36S (STATIC) inside Docker container..."
	$(RUNTIME) run --rm -v "$(PWD):/app" -w /app $(IMG_NAME) \
	/bin/bash -c "CC=$(CC_R36S_CONTAINER) $(CC_R36S_CONTAINER) -o $(EXECUTABLE_R36S)_static $(SOURCES) $(CFLAGS_R36S_CONTAINER) -static \$$(CC=$(CC_R36S_CONTAINER) /usr/bin/sdl2-config --static-libs)"
	@echo "Successfully built $(EXECUTABLE_R36S)_static for R36S."
	@echo "Transfer '$(EXECUTABLE_R36S)_static' to your device."

-include $(OBJECTS_LOCAL:.local.o=.d)

clean:
	@echo "Cleaning up build artifacts..."
	rm -f $(OBJECTS_LOCAL) $(EXECUTABLE_LOCAL) $(EXECUTABLE_R36S)
	rm -f $(patsubst %.c,%.local.d,$(SOURCES))
	@echo "Clean complete."
