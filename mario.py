from cs50 import get_int


def main():

    # Initialize height to zero
    height = 0

    # Whilst height is less than or equal to zero or greater than eight, ask user for integer
    while height <= 0 or height > 8:
        height = get_int("Height: ")

    # Loop numbers from 1 to height (height + 1 as range only creates a sequences up until but not including the last number)
    for i in range(1, height + 1):
        spaces = height - i
        blocks = height - spaces

        print_spaces(spaces)
        build_pyramid(blocks, "")
        print_spaces(2)
        build_pyramid(blocks, "\n")


# Print blocks for each half of pyramid
def build_pyramid(width, end):
    print("#" * width, end=end)


# Print n number of spaces
def print_spaces(n):
    print(" " * n, end="")


main()