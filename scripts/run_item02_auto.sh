#!/usr/bin/env sh
set -eu

cmake -S . -B build
cmake --build build --target Item02AutoTypeDeduction -j
./build/Item02AutoTypeDeduction
