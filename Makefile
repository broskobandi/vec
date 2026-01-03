PROJECT := vec
CC = gcc
CFLAGS = -Wall -Wextra -Wunused-result -Wconversion
CPPFLAGS := -Iinclude

BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIR := src
INC_DIR := include
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(wildcard $(INC_DIR)/*.h)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
TEST_DIR := test
TEST_MAIN := $(TEST_DIR)/test.c
TEST_EXE := $(BUILD_DIR)/test
WIN_BUILD_DIR := $(BUILD_DIR)/win
WIN_DLL := $(WIN_BUILD_DIR)/lib$(PROJECT).dll
WIN_A := $(WIN_BUILD_DIR)/lib$(PROJECT).a

LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include

.PHONY: debug release test run clean install win

debug: CC = bear --output $(BUILD_DIR)/compile_commands.json -- clang
debug: $(LIB_A) $(LIB_SO)

release: CFLAGS = -O3 -march=native -flto
release: $(LIB_A) $(LIB_SO)

test: $(TEST_EXE)

run: $(TEST_EXE)
	./$<

install: $(LIB_SO) $(LIB_A)
	cp $^ $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

clean:
	rm -rf $(BUILD_DIR)

win: CC = x86_64-w64-mingw32-gcc
win: CFLAGS = -O3 -march=native -flto
win: $(WIN_DLL) $(WIN_A)

$(WIN_A): $(OBJ) | $(WIN_BUILD_DIR)
	x86_64-w64-mingw32-ar rcs $@ $^

$(WIN_DLL): $(OBJ) | $(WIN_BUILD_DIR)
	$(CC) -shared $(CFALGS) $(CPPFLAGS) $^ -o $@

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TEST_EXE): $(TEST_MAIN) $(LIB_A) $(LIB_SO) $(INC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TEST_MAIN) $(LIB_SO) -o $(TEST_EXE)

$(WIN_BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@
