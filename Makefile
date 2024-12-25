CXX = g++
BUILD_DIR = build
DAYS = $(wildcard day_*)

# Convert slashes for Windows paths
BUILD_DIR_WIN = $(BUILD_DIR:\=/)

# Create an output name for each executable in the build directory
TARGETS = $(patsubst %, $(BUILD_DIR)/%, $(DAYS))

# Default target
all: $(TARGETS)

# Rule to build each target
$(BUILD_DIR)/%:
	@if not exist $(BUILD_DIR_WIN) mkdir $(BUILD_DIR_WIN)
	$(CXX) $*/*.cpp -o $@ -O3 -std=c++20

day_%: $(BUILD_DIR)/day_%
	@echo Built $< successfully.

run_all:
	$(CXX) run_all.cpp -o $@

# Clean build directory
clean:
	@if exist $(BUILD_DIR_WIN) rmdir /S /Q $(BUILD_DIR_WIN)

.PHONY: all clean
