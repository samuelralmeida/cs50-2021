#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int checkKey(string key);

int main(int argc, string argv[])
{
    // valid command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string key = argv[1];

    // check key
    int isValidKey = checkKey(key);
    if (isValidKey > 0)
    {
        return 1;
    }

    // get input text
    string text = get_string("plaintext: ");

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char letter;
        // uppercase
        if (text[i] >= 65 && text[i] <= 90)
        {
            letter = key[text[i] - 65];
            letter = toupper(letter);
        }
        // lowercase
        else if (text[i] >= 97 && text[i] <= 122)
        {
            letter = key[text[i] - 97];
            letter = tolower(letter);
        }
        // another chars
        else
        {
            letter = text[i];
        }
        text[i] = letter;
    }


    printf("ciphertext: %s\n", text);
    return 0;
}

int checkKey(string key)
{
    int sum = 0;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        // chek if all key are letters
        if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
        {
            sum += tolower(key[i]);
            continue;
        }
        else
        {
            printf("key have to be only letter\n");
            return 1;
        }
    }

    // the sum of uppercase key containing each letter exactly once is 2847
    if (sum != 2847)
    {
        printf("key have to contain each letter exactly once\n");
        return 1;
    }

    return 0;
}