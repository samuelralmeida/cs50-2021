#include "helpers.h"
#include <math.h>

int validatePixel(int x, int y, int height, int width);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate rgb avereage
            BYTE average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            if (average > 255)
            {
                average = 255;
            }
            // set average to all colors
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // because of swapr we need iterate only the width half
        int steps = width / 2;
        for (int j = 0; j < steps; j++)
        {
            // store pixel data to swap
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // store new pixels before replace for main image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            // inicializate color sums
            int blue = 0;
            int green = 0;
            int red = 0;
            float counter = 0.0;

            // loop for check each pixel around the main pixel
            for (int hf = -1; hf <= 1; hf++)
            {
                for (int wf = -1; wf <= 1; wf++)
                {
                    int nh = h + hf;
                    int nw = w + wf;

                    if (validatePixel(nh, nw, height, width))
                    {
                        blue += temp[nh][nw].rgbtBlue;
                        green += temp[nh][nw].rgbtGreen;
                        red += temp[nh][nw].rgbtRed;
                        counter++;
                    }
                }
            }

            red = round(red / counter);
            green = round(green / counter);
            blue = round(blue / counter);

            // check 255 limit
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }


            // calculate average RGB pixel for new image
            image[h][w].rgbtBlue = blue;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtRed = red;
        }
    }

    return;
}

int validatePixel(int nh, int nw, int height, int width)
{
    if (nh < 0 || nw < 0)
    {
        return 0;
    }
    else if (nw >= width)
    {
        return 0;
    }
    else if (nh >= height)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // store new pixels before replace for main image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // sobel matrix
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            // initializate color channels
            float red_gx = 0;
            float red_gy = 0;
            float green_gx = 0;
            float green_gy = 0;
            float blue_gx = 0;
            float blue_gy = 0;

            // loop for check each pixel around the main pixel
            for (int hf = -1; hf <= 1; hf++)
            {
                for (int wf = -1; wf <= 1; wf++)
                {
                    int nh = h + hf;
                    int nw = w + wf;

                    if (validatePixel(nh, nw, height, width))
                    {
                        red_gx += temp[nh][nw].rgbtRed * gx[hf + 1][wf + 1];
                        red_gy += temp[nh][nw].rgbtRed * gy[hf + 1][wf + 1];

                        green_gx += temp[nh][nw].rgbtGreen * gx[hf + 1][wf + 1];
                        green_gy += temp[nh][nw].rgbtGreen * gy[hf + 1][wf + 1];

                        blue_gx += temp[nh][nw].rgbtBlue * gx[hf + 1][wf + 1];
                        blue_gy += temp[nh][nw].rgbtBlue * gy[hf + 1][wf + 1];
                    }
                }
            }

            // calculate new color according to sobel
            int red = round(sqrt(red_gx * red_gx + red_gy * red_gy));
            int green = round(sqrt(green_gx * green_gx + green_gy * green_gy));
            int blue = round(sqrt(blue_gx * blue_gx + blue_gy * blue_gy));

            // check 255 limit
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // assign new pixels
            image[h][w].rgbtRed = red;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtBlue = blue;
        }
    }

    return;
}
