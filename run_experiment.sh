#!/bin/bash

set -e

# Parse named parameters
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        --start)
            export START="$2"
            shift; shift
            ;;
        --end)
            export END="$2"
            shift; shift
            ;;
        --experiments)
            export EXPERIMENTS="$2"
            shift; shift
            ;;
        --step)
            export STEP="$2"
            shift; shift
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Check if all required variables are set
if [[ -z "$START" || -z "$END" || -z "$EXPERIMENTS" || -z "$STEP" ]]; then
    echo "Usage: $0 --start <int> --end <int> --experiments <int> --step <int>"
    exit 1
fi

# Clean up previous output
[ -f "output.csv" ] && echo "Deleting old output.csv..." && rm output.csv

# Compile and run simulation
echo "Compiling..."
g++ -std=c++17 -O2 experiment.cpp -o experiment
echo "Running simulation..."
./experiment "$START" "$END" "$EXPERIMENTS" "$STEP"

# Run plotter
echo "Plotting results..."
python3 plotter.py