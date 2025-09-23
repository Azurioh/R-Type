#!/bin/bash

# Exit at first error
set -euo pipefail

# Function to display usage information
usage() {
    echo "Usage: $0 {server|client} {build|clean}"
    exit 1
}

# Check command line arguments
if [ "$#" -ne 2 ]; then
    usage
fi

# Define action and target directory variables
TARGET="$1"
ACTION="$2"

# Define paths variables based on the script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
TARGET_DIR="$PROJECT_ROOT/$TARGET"
BUILD_DIR="$TARGET_DIR/build"

# Check if target directory exists
if [ ! -d "$TARGET_DIR" ]; then
    echo "Target '$TARGET' does not exist at $TARGET_DIR"
    exit 1
fi

if command -v nproc >/dev/null 2>&1; then
    NPROC=$(nproc)
else
    NPROC=$(sysctl -n hw.ncpu)
fi

# Define clean and build functions
clean() {
    echo "Removing build directory for $TARGET"
    rm -rf "$BUILD_DIR"

    echo "Removing binary from project root"
    rm -f "$PROJECT_ROOT/r-type_$TARGET"
}

# Build function
build() {
    echo "Configuring $TARGET in $BUILD_DIR"
    cmake -S "$TARGET_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

    echo "Compiling $TARGET"
    cmake --build "$BUILD_DIR" -j"$NPROC"

    local exe="$BUILD_DIR/r-type_$TARGET"
    if [ -f "$exe" ]; then
        cp "$exe" "$PROJECT_ROOT/"
        echo "Copied $exe to $PROJECT_ROOT/"
    else
        echo "Binary $exe not found after build"
        exit 1
    fi
}

# Execute action
if [ "$ACTION" = "clean" ]; then
    clean "$TARGET"
elif [ "$ACTION" = "build" ]; then
    build "$TARGET"
else
    usage
fi
