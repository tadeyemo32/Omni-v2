#!/bin/bash

# Define the project root directory (where the script is run from)
PROJECT_DIR="$(pwd)"

# Define the bin and build directories
BIN_DIR="$PROJECT_DIR/bin"
BUILD_DIR="$PROJECT_DIR/build"

# Check if bin directory exists, if not, create it
if [ ! -d "$BIN_DIR" ]; then
    echo "Creating bin directory..."
    mkdir -p "$BIN_DIR"
fi

# Check if build directory exists, if not, create it
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Change to the build directory
cd "$BUILD_DIR"

# Run cmake to configure the project
echo "Running cmake in the build directory..."
cmake ..

# Run make to build the project
echo "Running make to build the project..."
make

# Check if omni_server exists in the bin directory
if [ -f "$BIN_DIR/omni_server" ]; then
    echo "Running omni_server..."
    # Run the omni_server executable
    "$BIN_DIR/omni_server"
else
    echo "Error: omni_server not found in the bin directory."
    exit 1
fi
