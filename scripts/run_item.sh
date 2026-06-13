#!/usr/bin/env sh
set -eu

usage() {
  echo "Usage: sh scripts/run_item.sh ITEM_NUMBER"
  echo "Example: sh scripts/run_item.sh 2"
}

if [ "$#" -ne 1 ]; then
  usage
  exit 1
fi

case "$1" in
  ''|*[!0-9]*)
    echo "ITEM_NUMBER must be a number."
    usage
    exit 1
    ;;
esac

if [ "$1" -lt 1 ] || [ "$1" -gt 42 ]; then
  echo "ITEM_NUMBER must be between 1 and 42."
  exit 1
fi

item_number=$(printf '%02d' "$1")
target="Item${item_number}"

set -- "src/item${item_number}_"*.cpp
source_file=$1

if [ ! -f "$source_file" ]; then
  echo "No source file found for item ${item_number}."
  exit 1
fi

if ! grep -Eq '(^|[[:space:]])int[[:space:]]+main[[:space:]]*\(' "$source_file"; then
  echo "${source_file} does not contain a main function yet."
  echo "Nothing to run for item ${item_number}."
  exit 0
fi

cmake -S . -B build
cmake --build build --target "$target" -j
"./build/${target}"
