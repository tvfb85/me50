import math
from cs50 import get_float


def main():

    # Initialize default variable for user input
    dollars = 0

    # Prompt user for float value
    while dollars <= 0:
        dollars = get_float("Change owed: ")

    # Create list of coin denominations
    denominations = [25, 10, 5, 1]

    # Convert dollars to cents
    cents = dollars * 100

    # Keep a count of coins
    coins = 0

    # Loop denominations, updating coin coin and remaining cents
    for i in denominations:
        coins += math.floor(cents / i)
        cents = cents % i

    # Print result
    print(f"{coins}")


main()