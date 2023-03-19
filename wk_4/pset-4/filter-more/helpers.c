#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Saves image[i][j] to temp var
            RGBTRIPLE temp = image[i][j];

            // Gets average values
            int ave = round((temp.rgbtBlue + temp.rgbtGreen + temp.rgbtRed) / 3.0);

            // Saves grayscale pixel to image
            temp.rgbtBlue = ave;
            temp.rgbtGreen = ave;
            temp.rgbtRed = ave;
            image[i][j] = temp;
        }
    }

    // Ends function
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2.0); j++)
        {
            // Swaps pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    // Ends function
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating copy of image
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j] = image[i][j];
        }
    }

    // Iterate through image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Getting the average colour
            int ave_red = 0;
            int ave_green = 0;
            int ave_blue = 0;
            int px_count = 0;

            // Goes through all adjecant pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    // Find out if we are out of picture
                    if (k < 0 || n < 0 || k > height - 1 || n > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        px_count++;
                        RGBTRIPLE temp = image2[k][n];
                        ave_red += temp.rgbtRed;
                        ave_green += temp.rgbtGreen;
                        ave_blue += temp.rgbtBlue;
                    }
                }
            }

            ave_red = round(ave_red / (float) px_count);
            ave_blue = round(ave_blue / (float) px_count);
            ave_green = round(ave_green / (float) px_count);

            // Assigns new colour value to pixel
            image[i][j].rgbtRed = ave_red;
            image[i][j].rgbtGreen = ave_green;
            image[i][j].rgbtBlue = ave_blue;
        }
    }

    // Ends Function
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Makes a copy of the image
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j] = image[i][j];
        }
    }

    // 2D arrays for sobel algorithm
    int sobelx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int sobely[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Iterates through image's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gets new pixel colour based on sobel operator
            int rgx = 0;
            int ggx = 0;
            int bgx = 0;

            int rgy = 0;
            int ggy = 0;
            int bgy = 0;

            // Goes through all adjacent pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    // Find out if we are out of picture
                    if (k < 0 || n < 0 || k > height - 1 || n > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        int sbl_idx = k - (i - 1);
                        int sbl_idy = n - (j - 1);

                        // Gets the value for sobel operator
                        rgx += image2[k][n].rgbtRed * sobelx[sbl_idx][sbl_idy];
                        ggx += image2[k][n].rgbtGreen * sobelx[sbl_idx][sbl_idy];
                        bgx += image2[k][n].rgbtBlue * sobelx[sbl_idx][sbl_idy];

                        rgy += image2[k][n].rgbtRed * sobely[sbl_idx][sbl_idy];
                        ggy += image2[k][n].rgbtGreen * sobely[sbl_idx][sbl_idy];
                        bgy += image2[k][n].rgbtBlue * sobely[sbl_idx][sbl_idy];
                    }
                }
            }

            // Gets colour from the formula sqrt(gx^2 + gy^2)
            int sbl_r = round(sqrt(pow(rgx, 2) + pow(rgy, 2)));
            int sbl_g = round(sqrt(pow(ggx, 2) + pow(ggy, 2)));
            int sbl_b = round(sqrt(pow(bgx, 2) + pow(bgy, 2)));

            // Checks for overflow
            if (sbl_r > 255)
            {
                sbl_r = 255;
            }

            if (sbl_g > 255)
            {
                sbl_g = 255;
            }

            if (sbl_b > 255)
            {
                sbl_b = 255;
            }

            // Assign new colour values to pixel
            image[i][j].rgbtRed = sbl_r;
            image[i][j].rgbtGreen = sbl_g;
            image[i][j].rgbtBlue = sbl_b;
        }
    }

    // Ends function
    return;
}
