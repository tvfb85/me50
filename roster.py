from cs50 import SQL
from sys import argv, exit

# Setup db connection
db = SQL("sqlite:///students.db")

# Check arguments length
if len(argv) != 2:
    print(f'Usage: {argv[0]} [house]')
    exit(1)

# Check second argument is one of the four student houses
elif argv[1] not in ['Gryffindor', 'Hufflepuff', 'Ravenclaw', 'Slytherin']:
    print(f'Usage: {argv[0]} [house]')
    exit(1)

# Execute db query to select students by house and sort
students = db.execute('SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first', argv[1])

# For each student print fullname followed by year of birth
for student in students:
    first = student['first']
    middle = ' ' + student['middle'] + ' ' if student['middle'] != None else ' '
    last = student['last']
    birth = student['birth']

    print(f'{first}{middle}{last}, born {birth}')

exit(0)
