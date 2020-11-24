from cs50 import SQL
from sys import argv, exit
import csv

# Setup db connection
db = SQL("sqlite:///students.db")

# Check arguments length
if len(argv) != 2:
    print(f'Usage: {argv[0]} [characters.csv]')
    exit(1)

# Check second argument is the filename expected
elif argv[1] != 'characters.csv':
    print(f'Unrecognised filename...\nUsage: {argv[0]} [characters.csv]')
    exit(1)

# Open csv file in read mode
with open(argv[1], 'r') as csv_file:

    # Setup reader
    reader = csv.DictReader(csv_file)

    # Loop rows of csv file
    for row in reader:

        # Split name to get list of first, middle and last names
        names = row['name'].split(' ')

        # If middle name exists, assign variables
        if len(names) == 3:
            first = names[0]
            middle = names[1]
            last = names[2]

        # Set middle name to None if only first and last name exist
        else:
            first = names[0]
            middle = None
            last = names[1]

        # Execute query to insert student into db
        db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)',
                   first, middle, last, row['house'], int(row['birth']))

exit(0)