# Compiler and flags
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Isrc -g

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Files (use substitution references for .o files)
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_OBJ_FILES = $(TEST_FILES:$(TEST_DIR)/%.c=$(BUILD_DIR)/test_%.o)

# Targets
TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/test_app

# Default target
all: $(TARGET)

# Build main application
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build and run test binary
test: $(OBJ_FILES) $(TEST_OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $(TEST_TARGET)
	./$(TEST_TARGET)

# Compile test object files
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all test clean
