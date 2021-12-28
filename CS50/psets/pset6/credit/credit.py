import sys
from cs50.cs50 import get_string


def main():
    # Get input from user
    cc_number: str = get_valid_card("Number: ")

    # Pass it through the checksum function
    valid: bool = checksum(cc_number)

    # If valid, pass through the checker else exit sys
    if valid:
        print(checker(cc_number))
    else:
        sys.exit("INVALID")


def get_valid_card(message: str) -> str:
    while True:
        card: str = get_string(message)
        if card.isnumeric():
            break
    return card


def checksum(number: str) -> bool:
    # Get the lenght of credit card number
    cc_length: int = len(number)

    # If length is not valid, return false
    if cc_length < 13 or cc_length > 16:
        return False

    sum: int = 0
    for i in range(0, cc_length, 2):
        # Add the odd number
        odd_index: int = cc_length - 1 - i
        if odd_index >= 0:
            sum += int(number[odd_index])

        # Multiply the even number from the back with 2
        even_index = cc_length - 2 - i
        product: str = str(int(number[even_index]) * 2)

        ## Add the digits together
        if even_index >= 0:
            for j in range(len(product)):
                sum += int(product[j])

        print(sum)

    # Return true if valid
    if sum % 10 == 0:
        return True
    else:
        return False


def checker(number: str) -> str:
    # Get identifier from check length and starting numbers
    length: int = check_length(number)
    starting: int = check_starting(number)

    # Multiply identifier
    result = length * starting

    # Return string based on identifier
    if result == 1:
        return "AMEX"
    elif result == 10:
        return "MASTERCARD"
    elif result in [9, 15]:
        return "VISA"
    else:
        return "INVALID"


def check_length(number: str) -> int:
    # Get length of number
    length: int = len(number)

    # Return identifier based on length
    if length == 15:
        return 1
    elif length == 13:
        return 3
    elif length == 16:
        return 5
    else:
        return 0


def check_starting(number: str) -> int:
    # Get the starting
    starting: int = int(number[0])

    # If first number is 4, it's a VISA, else, check first 2 numbers
    if starting == 4:
        return 3
    else:
        starting = int(number[:2])

    # Check first 2 number for non-VISA cards
    if starting in [34, 37]:
        return 1
    elif starting in [51, 52, 53, 54, 55]:
        return 2
    else:
        return 0


if __name__ == "__main__":
    main()
