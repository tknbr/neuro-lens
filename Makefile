CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = -lpng # Linking with libpng for image_io.c. Adjust according to used libraries.
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)/obj

# Automatically find all C files in the src directory and its subdirectories
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
# Replace the src directory and .c extension with the obj directory and .o extension
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable name
TARGET = $(BIN_DIR)/neuro-lens

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Pattern rule for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)
