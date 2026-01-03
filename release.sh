#!/bin/env sh

make \
	CC=gcc \
	CFLAGS="-Wall -Werror -Wunused-result -Wconversion -O3 -march=native -flto" \
	CPPFLAGS="-Include -DNDEBUG" \
	BUILD_DIR=build/linux/release
