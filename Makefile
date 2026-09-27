# ==== PROPERTIES ==== #
EXE = ramble
VER = 0.0.1-alpha

CFLAGS = -std=c++20 -Wall
LIBS   = -lglfw -lGL

# ==== PATHS ==== #
SRC  = src/*.cpp
SRC += src/ramble/*.cpp
SRC += src/glad/glad.c
SRC += src/stb_image/stb_image.c

DEBUG_DIR   = build/debug
RELEASE_DIR = build/release

# ==== COMMANDS ==== #
BUILD  = mkdir -p $(DEBUG_DIR)/v$(VER)
BUILD += && rm -rf $(DEBUG_DIR)/v$(VER)/resources
BUILD += && cp -r resources $(DEBUG_DIR)/v$(VER)
BUILD += && g++ $(CFLAGS) $(SRC) -o $(DEBUG_DIR)/v$(VER)/$(EXE) $(LIBS)

PUBLISH  = mkdir -p $(RELEASE_DIR)/v$(VER)
PUBLISH += && rm -rf $(RELEASE_DIR)/v$(VER)/resources
PUBLISH += && cp -r resources $(RELEASE_DIR)/v$(VER)
PUBLISH += && g++ $(CFLAGS) $(SRC) -o $(RELEASE_DIR)/v$(VER)/$(EXE) $(LIBS)

RUN    = $(DEBUG_DIR)/v$(VER)/$(EXE)
PUBRUN = $(RELEASE_DIR)/v$(VER)/$(EXE)

CLEAN    = rm -rf $(DEBUG_DIR)/v$(VER)
PUBCLEAN = rm -rf $(RELEASE_DIR)/v$(VER)

.PHONY: build run clean test

# ==== BUILD ==== #
build:
	$(BUILD)

run:
	$(RUN)

test:
	$(BUILD)
	$(RUN)

clean:
	$(CLEAN)

# ==== PUBLISH ==== #
publish:
	$(PUBLISH)

pubrun:
	$(PUBRUN)


pubtest:
	$(BUILD)
	$(PUBRUN)

pubclean:
	$(PUBCLEAN)
