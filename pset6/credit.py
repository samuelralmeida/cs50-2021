from cs50 import get_int
import sys


def main():

    # get the card number
    number = get_int("Number: ")

    # check number length
    if number < 1000000000000 or number > 9999999999999999:
        print("INVALID")
        sys.exit(0)

    sumProductsDigits = 0
    sumNoProductsDigits = 0
    firstTwoDigits = 0
    rest = 0
    count = 1

    while number > 0:

        # number position indicates common sum
        if (count % 2) != 0:
            rest = number % 10
            sumNoProductsDigits = sumNoProductsDigits + rest

        # number position indicates sum of product
        if (count % 2) == 0:
            rest = number % 10
            rest = rest * 2

            # sum rest digits when it is greatter than 10
            while rest > 9:
                r = rest % 10
                rest = int(rest / 10) + r

            sumProductsDigits = sumProductsDigits + rest

        # prepare number for next iteration
        number = int(number / 10)

        # store first two digts from number to check card flag
        if number > 9 and number < 100:
            firstTwoDigits = number

        count += 1

    # result for validation
    result = sumProductsDigits + sumNoProductsDigits
    if result % 10 != 0:
        print("INVALID")
        sys.exit(0)

    # check card flag
    checkCardFlag(firstTwoDigits)


def checkCardFlag(firstTwoDigits):
    if firstTwoDigits == 34 or firstTwoDigits == 37:
        print("AMEX")
    elif firstTwoDigits == 51 or firstTwoDigits == 52 or firstTwoDigits == 53 or firstTwoDigits == 54 or firstTwoDigits == 55:
        print("MASTERCARD")
    elif int(firstTwoDigits / 10) == 4:
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()

