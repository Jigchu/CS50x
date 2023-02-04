#include <cs50.h>
#include <stdio.h>

void print_pyramid(int h);

int main(void)
{
    //gets height (within 1 to 8)
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //prints the pyramids
    print_pyramid(height);
}

void print_pyramid(int h)
{
    //iterates through the layers (1-height)
    for (int i = 1; i <= h; i++)
    {
        //prints row of first pyramid
        for (int j = 0; j < (h - i); j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //separates the first pyramid from the second
        printf("  ");
        //prints row of second pyramid
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        //moves pointer to next line
        printf("\n");
    }
}