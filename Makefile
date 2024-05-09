CC := gcc
CFLAGS := -Wall -Wextra -O2
LIB_STATIC_NAME := build/libfse.a
LIB_SHARED_NAME := libfse.so
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
BIN_TARGET := $(BIN_DIR)/fallout_save_editor

.PHONY: all clean library-shared cli install uninstall

all: library-shared cli

library-shared: CFLAGS += -fPIC
library-shared: $(LIB_DIR)/$(LIB_SHARED_NAME)

$(LIB_DIR)/$(LIB_SHARED_NAME): $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(CC) -shared -o $@ $(OBJS)

cli: $(BIN_TARGET)

$(BIN_TARGET): $(CLI_OBJS) $(LIB_STATIC_NAME)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(CLI_OBJS) -L$(OBJ_DIR) -lfse

$(LIB_STATIC_NAME): $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(AR) rcs $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CLI_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/$(LIB_SHARED_NAME)
	rm -f $(BIN_TARGET)
	rm -rf $(OBJ_DIR)

PREFIX := /usr/local
BIN_INSTALL_DIR := $(PREFIX)/bin
LIB_INSTALL_DIR := $(PREFIX)/lib
INCLUDE_INSTALL_DIR := $(PREFIX)/include/fse

install: install-lib-shared install-cli install-headers

install-lib-shared: library-shared
	@mkdir -p $(LIB_INSTALL_DIR)
	install -m 644 $(LIB_DIR)/$(LIB_SHARED_NAME) $(LIB_INSTALL_DIR)
	ldconfig

install-cli: $(BIN_TARGET)
	@mkdir -p $(BIN_INSTALL_DIR)
	install -m 755 $< $(BIN_INSTALL_DIR)

install-headers:
	@mkdir -p $(INCLUDE_INSTALL_DIR)
	cp -r ./include/fse/* $(INCLUDE_INSTALL_DIR)

uninstall:
	rm -f $(BIN_INSTALL_DIR)/$(notdir $(BIN_TARGET))
	rm -f $(LIB_INSTALL_DIR)/$(LIB_SHARED_NAME)
	rm -rf $(INCLUDE_INSTALL_DIR)