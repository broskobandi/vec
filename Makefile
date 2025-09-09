# Project
PROJECT := vec
FIND_CC := $(shell command -v clang || command -v gcc)
CC := $(FIND_CC)
CFLAGS := -Wall -Wextra -Werror -Wunused-result -Wconversion
CPPFLAGS := -Iinclude -Isrc
LDFLAGS := -L/usr/local/lib -lmem_alloc

# Dirs
INC_DIR := include
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
OBJ_DIR := obj
DOC_DIR := doc
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h
INC_PRIV := $(wildcard $(SRC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_MAIN := $(TEST_DIR)/test.c
TEST_EXE := $(BUILD_DIR)/test
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so

# Rules
.PHONY: all test clean install uninstall doc

all: $(LIB_A) $(LIB_SO)

test: CC = bear -- $(FIND_CC)
test: CPPFLAGS += test
test: $(TEST_EXE)
	./$<

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) compile_commands.json

install:
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

uninstall:
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_SO)))
	rm $(addprefix $(LIB_INSTALL_DIR)/, $(notdir $(LIB_A)))
	rm $(addprefix $(INC_INSTALL_DIR)/, $(notdir $(INC)))

doc:
	doxygen

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(TEST_EXE): $(TEST_MAIN) $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(INC_PRIV) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@
