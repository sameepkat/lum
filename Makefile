CXX := g++
CXX_STANDARD := c++23

PROJECT_NAME := lum

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

TARGET := $(BIN_DIR)/$(PROJECT_NAME)

PREFIX ?= /usr/local

CPPFLAGS := -I$(INCLUDE_DIR) -DLUM_STD_PATH=\"$(PREFIX)/share/lum/std\"
CXXFLAGS := -std=$(CXX_STANDARD) -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2

SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPENDS := $(OBJECTS:.o=.d)

TEST_DIR := tests
PASS_TESTS := $(shell find $(TEST_DIR)/pass -name "*.lum" | sort)
FAIL_TESTS := $(shell find $(TEST_DIR)/fail -name "*.lum" | sort)

.PHONY: all debug release run clean rebuild dirs test test-pass test-fail

all: debug

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: dirs $(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: dirs $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

install: release
		install -d $(DESTDIR)$(PREFIX)/bin
		install -d $(DESTDIR)$(PREFIX)/share/lum/std
		install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin/$(PROJECT_NAME)
	cp -R std/* $(DESTDIR)$(PREFIX)/share/lum/std

uninstall:
		rm -f $(DESTDIR)$(PREFIX)/bin/$(PROJECT_NAME)
		rm -rf $(DESTDIR)$(PREFIX)/share/lum

dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

run: debug
	./$(TARGET) examples/hello_world.lum

test: test-pass

test-pass: debug
	@for test in $(PASS_TESTS); do \
		echo "Running $$test"; \
			./$(TARGET) $$test || exit 1; \
	done

test-fail: debug
	@for test in $(FAIL_TESTS); do \
		echo "Running $$test"; \
		./$(TARGET) $$test && exit 1 || true; \
	done

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean debug

-include $(DEPENDS)
