CC = g++
TARGET_NAME = vm-translator
OUT_DIR = out
TARGET = $(OUT_DIR)/$(TARGET_NAME)
SRCS = src/main.cpp src/parser.cpp src/code.cpp src/utils.cpp
OBJS = $(SRCS:src/%.cpp=$(OUT_DIR)/%.o)

$(TARGET): $(OBJS)
	@mkdir -p $(OUT_DIR)
	@$(CC) $^ -o $@
	@echo "Built $(TARGET_NAME): $@"

$(OUT_DIR)/%.o: src/%.cpp
	@mkdir -p $(OUT_DIR)
	@$(CC) -c $< -o $@

clean:
	@rm -rf out
	@echo "Cleaned all builds."

.PHONY: all run clean
