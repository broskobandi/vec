#!/bin/env sh

make test &&
./release.sh &&
./win-debug.sh &&
./win-release.sh
