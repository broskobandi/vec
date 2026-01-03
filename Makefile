# Project
COMPILER_COMMANDS := build/compile_commands.json
PROJECT := vec
CC ?= bear --output $(COMPILER_COMMANDS) -- clang
AR ?= ar
CFLAGS ?= -Wall -Werror -Wunused-result -Wconversion
CPPFLAGS ?= -Iinclude

# Dirs
BUILD_DIR ?= build/linux/debug
OBJ_DIR := $(BUILD_DIR)/obj
LIB_DIR := $(BUILD_DIR)/lib
INC_DIR := include
SRC_DIR := src
TEST_DIR := test
EXAMPLE_DIR := example
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(wildcard $(INC_DIR)/*.h)
TEST_MAIN := $(TEST_DIR)/test.c
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c
LIB_SH_NAME ?= lib$(PROJECT).so
LIB_ST_NAME ?= lib$(PROJECT).a

# Targets
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB_SH := $(LIB_DIR)/$(LIB_SH_NAME)
LIB_ST := $(LIB_DIR)/$(LIB_ST_NAME)
TEST_BIN := $(BUILD_DIR)/test
EXAMPLE_BIN := $(BUILD_DIR)/example

.PHONY: all test example clean distclean install

all: $(LIB_SH) $(LIB_ST)

test: $(TEST_BIN)
	@./$<

example: $(EXAMPLE_BIN)
	./$<

clean:
	rm -rf $(LIB_SH) $(LIB_ST) $(COMPILER_COMMANDS) $(OBJ)

distclean:
	rm -rf build

install: $(LIB_SH) $(LIB_ST)
	cp $^ $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

$(LIB_SH): $(OBJ) | $(LIB_DIR)
	@echo Building $@...
	@$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@
	@echo Done"\n"

$(LIB_ST): $(OBJ) | $(LIB_DIR)
	@echo Building $@...
	@$(AR) rcs $@ $^
	@echo Done"\n"

$(TEST_BIN): $(TEST_MAIN) $(LIB_SH) $(LIB_ST) | $(BUILD_DIR)
	@echo Building $@...
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -L$(LIB_DIR) -l$(PROJECT)
	@echo Done"\n"

$(EXAMPLE_BIN): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	@echo Building $@...
	@$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -l$(PROJECT)
	@echo Done"\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h | $(OBJ_DIR)
	@echo Building $@...
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	@echo Done"\n"

$(BUILD_DIR):
	@mkdir -p $@

$(LIB_DIR):
	@mkdir -p $@

$(OBJ_DIR):
	@mkdir -p $@
