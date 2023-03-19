#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
   for (int i = 0; i < height; i++)
   {
        for (int j = 0; j < width; j++)
        {
            // A temp var to store the rgb triple of pixel
            RGBTRIPLE temp = image[i][j];

            // Edit rgb triple of pixel
            if (temp.rgbtBlue == 0 && temp.rgbtGreen == 0 && temp.rgbtRed == 0)
            {
                temp.rgbtBlue = 255;
                temp.rgbtGreen = 255;
                temp.rgbtRed = 255;
            }

            image[i][j] = temp;
        }
   }

   return;
}
