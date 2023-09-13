#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // software
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image'\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    BYTE buffer[512];
    int counter = 0;
    int opened = 0;

    FILE *outptr = NULL;
    char filename[8];

    while (fread(&buffer, 512, 1, inptr) == 1)
    {
        // check first four bytes if they are jpeg assignature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {

            // checks if an opened file already exists
            if (opened == 1)
            {
                // close opened image
                fclose(outptr);
                opened = 0;
            }

            // create name for image that has been founded
            sprintf(filename, "%03d.jpg", counter);

            // open file for new image
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 1;
            }
            opened = 1;

            // write new image
            fwrite(&buffer, 512, 1, outptr);
            counter++;
        }
        else if (opened == 1)
        {
            fwrite(&buffer, 512, 1, outptr);
        }

    }

    if (opened == 1)
    {
        fclose(outptr);
    }
    fclose(inptr);
}