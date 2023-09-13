#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get input text
    string text = get_string("Text: ");

    // counters
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // count only if char is a letter
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
        // count blank space
        else if (text[i] == 32)
        {
            words++;
        }
        // count sentences mark (! = 33; . = 46; ? 63)
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    // sum last word
    words++;


    // average number of letters per 100 words
    float l = (letters / (float) words) * 100;

    //average number of sentences per 100 words
    float s = (sentences / (float) words) * 100;

    int grade = (int) round(0.0588 * l - 0.296 * s - 15.8);

    // check grade
    if (grade < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
