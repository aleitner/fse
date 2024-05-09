CC := gcc
CFLAGS := -Wall -Wextra -O2 -fPIC
LIB_NAME := libfse.so
INCLUDE_DIRS := -I./include
LIB_DIR := ./lib
SRC_DIR := ./src
OBJ_DIR := ./build
BIN_DIR := ./bin
CLI_DIR := ./cli

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CLI_SRCS := $(wildcard $(CLI_DIR)/*.c)
CLI_OBJS := $(CLI_SRCS:$(CLI_DIR)/%.c=$(OBJ_DIR)/%.o)
BIN_TARGET := $(BIN_DIR)/fse_read_save_dat

.PHONY: all clean library cli install

all: library cli

library: $(OBJS)
	@mkdir -p $(LIB_DIR)  # This causes the error if LIB_DIR is not set correctly
	$(CC) -shared -o $(LIB_DIR)/$(LIB_NAME) $(OBJS)

all: library cli

library: $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $(LIB_DIR)/$(LIB_NAME) $(OBJS)

cli: $(BIN_TARGET)

$(BIN_TARGET): $(CLI_OBJS) library
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(CLI_OBJS) -L$(LIB_DIR) -lfse

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CLI_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/$(LIB_NAME)
	rm -f $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)

PREFIX := /usr/local
BIN_INSTALL_DIR := $(PREFIX)/bin
LIB_INSTALL_DIR := $(PREFIX)/lib
INCLUDE_INSTALL_DIR := $(PREFIX)/include/fse

install:
	@mkdir -p $(BIN_INSTALL_DIR)
	@mkdir -p $(LIB_INSTALL_DIR)
	@mkdir -p $(INCLUDE_INSTALL_DIR)
	install -m 755 $(BIN_TARGET) $(BIN_INSTALL_DIR)
	install -m 644 $(LIB_DIR)/$(LIB_NAME) $(LIB_INSTALL_DIR)
	cp -r ./include/fse/* $(INCLUDE_INSTALL_DIR)
	ldconfig $(LIB_INSTALL_DIR)

uninstall:
	rm -f $(BIN_INSTALL_DIR)/$(notdir $(BIN_TARGET))
	rm -f $(LIB_INSTALL_DIR)/$(LIB_NAME)
	rm -rf $(INCLUDE_INSTALL_DIR)