#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get population start size
    int population;
    do
    {
        population = get_int("Start size: ");
    }
    while (population < 9);

    // get population end size
    int end_population;
    do
    {
        end_population = get_int("End size: ");
    }
    while (population > end_population);

    // calculate number of years until we reach threshold
    int years = 0;
    while (population < end_population)
    {
        population = population + (population / 3) - (population / 4);
        years++;
    }

    // print number of years
    printf("Years: %d\n", years);
}