#!/bin/sh

# Assigning command line arguments to variables
filesdir=$1
searchstr=$2

# Check if both arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Error: Two arguments are required - a directory path and a search string."
    exit 1
fi

# Check if the first argument is a directory
if [ ! -d "$filesdir" ]; then
    echo "Error: The specified directory does not exist on the filesystem."
    exit 1
fi

# Count the number of files in the directory and subdirectories
num_files=$(find "$filesdir" -type f | wc -l)

# Count the number of matching lines across all files
num_matching_lines=$(grep -r "$searchstr" "$filesdir" | wc -l)

# Print the result
echo "The number of files are $num_files and the number of matching lines are $num_matching_lines"
