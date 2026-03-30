CC = g++
MODE ?= debug

ifeq ($(MODE), debug)
    CFLAGS = -g -Wall -Wextra -DDEBUG
else
    CFLAGS = -O2 -DNDEBUG -Wall -Wextra
endif

TARGET_NAME = vm-translator
OUT_DIR = out
TARGET = $(OUT_DIR)/$(TARGET_NAME)
SRCS = src/main.cpp src/utils.cpp src/code.cpp src/parser.cpp
OBJS = $(SRCS:src/%.cpp=$(OUT_DIR)/%.o)

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo "Built $(TARGET_NAME): $@"

$(OUT_DIR)/%.o: src/%.cpp
	@mkdir -p $(OUT_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf out
	@echo "Cleaned all builds."

.PHONY: all run clean
