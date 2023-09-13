#include <stdio.h>
#include <cs50.h>

void build(int number, string character);

int main(void)
{
    // get the pyramid height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // brick char
    string brick = "#";
    // space char
    string space = " ";

    // build pyramid
    int count = 1;
    while (count <= height)
    {
        build(height - count, space);
        build(count, brick);
        build(2, space);
        build(count, brick);
        printf("\n");
        count++;
    }
}

void build(int number, string character)
{
    int count = 0;
    while (count < number)
    {
        printf("%s", character);
        count++;
    }
}
