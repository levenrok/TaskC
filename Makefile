BIN=$(BUILD_DIR)/taskc

CC=clang
STD=c11

CFLAGS=-g -Wall -Wpedantic

LDFLAGS=-g
LDLIBS=-lsqlite3

# File types
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Directories
SRC_DIR=src
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

.PHONY: all launch pre clean

all: $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | pre
	$(CC) -std=$(STD) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

launch: $(BIN)
	./$(BIN)

pre:
	mkdir -p $(OBJ_DIR) $(LIB_DIR)

clean:
	$(RM) -r $(BUILD_DIR)
