#!/bin/bash

# Ensure SFML is installed
command -v g++ >/dev/null 2>&1 || { echo >&2 "g++ is required but not installed. Aborting."; exit 1; }

# Compile the Metronome program
g++ Metronome_try1.cpp -o Metronome_try1 -lsfml-audio -lsfml-system

# Check if compilation succeeded
if [[ ! -f Metronome_try1 ]]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Run the program
./Metronome_try1
