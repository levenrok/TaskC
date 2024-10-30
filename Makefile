BIN=$(BUILD_DIR)/taskc

CC=clang
STD=c11

CFLAGS=-g -Wall -Wpedantic -I$(INCLUDE_DIR)

LDFLAGS=-g
LDLIBS=-lsqlite3

# File types
SRCS=$(SRC_DIR)/main.c\
	 $(SRC_DIR)/db_func.c
OBJS=$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Directories
SRC_DIR=src
INCLUDE_DIR=$(SRC_DIR)/include
BUILD_DIR=build
OBJ_DIR=$(BUILD_DIR)/obj

.PHONY: all launch pre clean

all: $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | pre
	@echo "Compiling $^"
	$(CC) -std=$(STD) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	@echo "Linking $^"
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

launch: $(BIN)
	./$(BIN)

pre:
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(BUILD_DIR)
