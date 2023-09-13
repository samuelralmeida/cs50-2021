#include <stdio.h>
#include <cs50.h>

void CheckCardFlag(int firstTwoDigits);

int main(void)
{
    // get the card number
    long number;
    number = get_long("Number: ");

    // check number length
    if (number < 1000000000000 || number > 9999999999999999)
    {
        printf("INVALID\n");
        return 0;
    }

    // initiate control variables
    int sumProductsDigits = 0;
    int sumNoProductsDigits = 0;
    int firstTwoDigits = 0;
    int rest = 0;
    int count = 1;


    while (number > 0)
    {

        // number position indicates common sum
        if (count % 2 != 0)
        {
            rest = number % 10;
            sumNoProductsDigits = sumNoProductsDigits + rest;
        }

        // number position indicates sum of product
        if (count % 2 == 0)
        {
            rest = number % 10;
            rest = rest * 2;

            // sum rest digits when it is greatter than 10
            while (rest > 9)
            {
                int r = rest % 10;
                rest = (rest / 10) + r;
            }

            sumProductsDigits = sumProductsDigits + rest;
        }


        // prepare number for next iteration
        number = number / 10;

        // store first two digts from number to check card flag
        if (number > 9 && number < 100)
        {
            firstTwoDigits = number;
        }

        count++;
    }

    // result for validation
    int result = sumProductsDigits + sumNoProductsDigits;
    if (result % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // check card flag
    CheckCardFlag(firstTwoDigits);
}

void CheckCardFlag(int firstTwoDigits)
{
    if (firstTwoDigits == 34 || firstTwoDigits == 37)
    {
        printf("AMEX\n");
    }
    else if (firstTwoDigits == 51 || firstTwoDigits == 52 || firstTwoDigits == 53 || firstTwoDigits == 54 || firstTwoDigits == 55)
    {
        printf("MASTERCARD\n");
    }
    else if (firstTwoDigits / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
