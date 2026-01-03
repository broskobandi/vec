#!/bin/env sh

cp build/linux/release/lib/libvec.so /usr/local/lib &&
cp build/linux/release/lib/libvec.a /usr/local/lib &&
cp include/*.h /usr/local/include &&
ldconfig
