#!/bin/env sh

make CC=x86_64-w64-mingw32-gcc \
	AR=x86_64-w64-mingw32-ar \
	BUILD_DIR=build/win/debug \
	LIB_SH_NAME="lib\$(PROJECT).dll" \
	LIB_ST_NAME="lib\$(PROJECT).a" \
