#!/bin/bash

# Output file to store the extracted values
output_file="extracted_values.log"

# Delete the existing output file (if it exists)
rm -f "$output_file"

# Find and process all txt files with the format output-x-core.txt, save to an array and sort them
mapfile -t files < <(find . -type f -name 'output-*-core.txt' | sort -t '-' -k 2n)

# Iterate through the sorted files
for file in "${files[@]}"; do
    # Extract the value using grep and save it in a variable
    value=$(grep -oP 'Finished in \K[0-9.]+ seconds' "$file")

    # Extract the core number from the file name
    core=$(echo "$file" | sed -n 's/.*output-\(.*\)-core.txt/\1-core/p')

    # Append the extracted value to the output file with the modified file name
    echo "$core: $value" >> "$output_file"
done
