CC = gcc
# Updated CFLAGS with sanitization and debug information flags
CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=leak -fsanitize=undefined
SRC_DIR = .
OBJ_DIR = obj
DATA_DIR = ../data

# List your source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
EXECUTABLE = detectCycles

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE) $(DATA_DIR)/graphmatrix-1.txt
