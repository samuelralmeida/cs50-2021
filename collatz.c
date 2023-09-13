#include <cs50.h>
#include <stdio.h>

int collatz(int value);

int main(void)
{
    int input = get_int("input: ");
    int steps = collatz(input);
    printf("Steps: %d\n", steps);
}

int collatz(int value)
{
    // base case
    if (value == 1)
    {
        return 0;
    }
    // even numbers
    else if (value % 2 == 0)
    {
        return 1 + collatz(value/2);
    }
    // odd numbers
    else
    {
        return 1 + collatz(3*value + 1);
    }
}