CXX := g++
CXX_STANDARD := c++23

PROJECT_NAME := lum

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

TARGET := $(BIN_DIR)/$(PROJECT_NAME)

CXXFLAGS := -std=$(CXX_STANDARD) -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2

SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

.PHONY = all debug release run clean rebuild dirs

all: debug

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: dirs $(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: dirs $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

run: debug
	./$(TARGET) examples/hello_world.lum

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean debug

-include $(DEPENDS)
