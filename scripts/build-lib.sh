#!/bin/bash

# Exit at first error
set -euo pipefail

# Function to display usage information
usage() {
    echo "Usage: $0 {Render|HMI} {lib-name} {build|clean}"
    exit 1
}

# Check command line arguments
if [ "$#" -ne 3 ]; then
    usage
fi

# Define action and target directory variables
LIB_CATEGORY="$1"
LIB_NAME="$2"
ACTION="$3"

# Define paths variables based on the script location
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
LIB_ROOT="$PROJECT_ROOT/lib/$LIB_CATEGORY/$LIB_NAME"
BUILD_DIR="$LIB_ROOT/build"

# Check if target directory exists
if [ ! -d "$LIB_ROOT" ]; then
    echo "Library '$LIB_NAME' does not exist at $LIB_ROOT"
    exit 1
fi

# Define clean and build functions
clean() {
    echo "Removing build directory for $LIB_NAME"
    rm -rf "$BUILD_DIR"
}

build() {
    echo "Configuring $LIB_NAME in $BUILD_DIR"
    cmake -S "$LIB_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

    echo "Compiling $LIB_NAME"
    cmake --build "$BUILD_DIR" -j"$(nproc)"
}

# Execute action
if [ "$ACTION" = "clean" ]; then
    clean "$LIB_NAME"
elif [ "$ACTION" = "build" ]; then
    build "$LIB_NAME"
else
    usage
fi
