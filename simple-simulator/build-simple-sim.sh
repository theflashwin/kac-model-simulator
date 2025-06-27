#!/bin/bash

# Exit immediately on any error
set -e

# Set the source and output file names
SRC="simple_simulator.cpp"
OUT="simple_simulator"

# Use LLVM from Homebrew
LLVM_PREFIX=$(brew --prefix llvm)
CXX="$LLVM_PREFIX/bin/clang++"

# Compile the file with C++17 and standard flags
echo "Compiling $SRC..."
$CXX -std=c++17 "$SRC" -o "$OUT"

echo "Build complete: ./$OUT"
