from sys import argv, exit
import csv
import re

# Validate number of command-line arguments
if len(argv) != 3:
    print(f'Usage: {argv[0]} [data.csv] [sequence.txt]')
    exit(1)


def main():

    # Initialize empty dict to hold csv data
    csv_data = {}

    # Initialize empty list to store longest repeated sequence for each STR
    str_counts = []

    # Read csv file
    with open(argv[1], 'r') as csvfile:
        reader = csv.reader(csvfile)

        # Get headers from csv file
        headers = next(reader, None)

        # Store each person as a key in the dict with their corresponding STR values
        for row in reader:
            csv_data[row[0]] = row[1:]

    # Read DNA sequence from text file, removing new line at end of file
    with open(argv[2], 'r') as txtfile:
        sequence = txtfile.read().replace('\n', '')

    # Delete the names column from list of headers
    del headers[0]

    # Loop the remaining headers
    for key in headers:

        # Compile regex pattern with repeating capture group (for efficiency)
        regex = re.compile(rf'({key})\1*')

        # Save match for each match found in sequence
        match = [match for match in re.finditer(regex, sequence)]

        # Initialize variable to store the highest number of times an STR sequence is repeated
        repeat_count = 0

        # Loop matches
        for i in range(len(match)):

            # Access capture group for each match and count number of times the STR sequence is repeated
            if match[i].group().count(key) > repeat_count:

                # Update total if a longer repeated sequence is found
                repeat_count = match[i].group().count(key)

        # For each STR, convert count of highest repeated sequence to string and add to str_count list
        str_counts.append(str(repeat_count))

    # Convert csv_data dict to list and loop each key and value pair
    for key, value in csv_data.items():

        # Check each value for match with STR count from DNA sequence
        if value == str_counts:

            # Print name if match is found
            print(key)
            exit(0)

    # Return response if no matches found
    print("No match")
    exit(0)


main()