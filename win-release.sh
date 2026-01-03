#!/bin/env sh

make CC=x86_64-w64-mingw32-gcc \
	AR=x86_64-w64-mingw32-ar \
	CFLAGS="-Wall -Wextra -Wunused-result -Wconversion -O3 -march=native -flto" \
	CPPFLAGS="-Iinclude -DNDEBUG" \
	BUILD_DIR=build/win/release \
	LIB_SH_NAME="lib\$(PROJECT).dll" \
	LIB_ST_NAME="lib\$(PROJECT).a" \
