CC = gcc
CFLAGS = -Wall -Wextra

SRC_DIR = src
LIB_DIR = src/lib
BUILD_DIR = build

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(LIB_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES)) $(patsubst $(LIB_DIR)/%.c,$(BUILD_DIR)/%.o,$(LIB_FILES))

$(BUILD_DIR)/main: $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lm
	@echo "Executable 'main' built successfully!"
	@$(MAKE) clean

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(LIB_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/*.o 
	@echo "Cleaned object files"

.PHONY: all clean

# Set the default target to build the main executable
.DEFAULT_GOAL := $(BUILD_DIR)/main