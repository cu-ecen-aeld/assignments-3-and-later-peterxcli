#!/bin/bash

# Assigning command line arguments to variables
writefile=$1
writestr=$2

# Check if both arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments are required - a file path and a text string to write."
    exit 1
fi

# Extract the directory path from the full file path
dirpath=$(dirname "$writefile")

# Create the directory if it does not exist
if ! mkdir -p "$dirpath"; then
    echo "Error: Failed to create directory path for $writefile."
    exit 1
fi

# Attempt to write the text string to the file, creating or overwriting the file
if echo "$writestr" > "$writefile"; then
    echo "File created and written to successfully."
else
    echo "Error: Failed to write to $writefile."
    exit 1
fi
