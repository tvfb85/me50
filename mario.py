from cs50 import get_int

# Initialize height to zero
height = 0

# Whilst height is less than or equal to zero or greater than eight, ask user for integer
while height <= 0 or height > 8:
    height = get_int("Height: ")

# Loop numbers from 1 to height (height + 1 as range only creates a sequences up until but not including the last number)
for i in range(1, height + 1):

    # Calculate spaces and blocks per row
    spaces = height - i
    blocks = height - spaces

    # Print spaces for row and override default newline
    print(" " * spaces, end="")

    # Print blocks for row
    print("#" * blocks)