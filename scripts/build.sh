#!/bin/bash

# Exit at first error
set -e

# Check command line arguments
if [ "$#" -ne 2 ]; then
    exit 1
fi

# Define action and target directory variables
ACTION="$1"
TARGET_DIR="$2"

# Function to clean build artifacts
clean() {
    local target_dir="$1"

    rm -rf "$target_dir/build"

    rm -f "$target_dir/r-type_client"
    rm -f "$target_dir/r-type_server"
}

# Function to build the project
build() {
    local target_dir="$1"
    local build_dir="$target_dir/build"

    rm -rf "$build_dir" && mkdir -p "$build_dir"

    cd "$build_dir"

    cmake ".." -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build "."

    if [ -f "r-type_client" ]; then
        cp "r-type_client" ".."
    elif [ -f "r-type_server" ]; then
        cp "r-type_server" ".."
    else
        exit 1
    fi

    cd - > /dev/null
}

# Execute action
if [ "$ACTION" = "clean" ]; then
    clean "$TARGET_DIR"
    exit 0
elif [ "$ACTION" = "build" ]; then
    build "$TARGET_DIR"
    exit 0
else
    exit 1
fi
