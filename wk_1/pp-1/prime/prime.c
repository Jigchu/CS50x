#include <cs50.h>
#include <stdio.h>

bool prime(int number);
int factor(int num);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    //checks if number is 2
    if (number == 2)
    {
        return true;
    }
    //checks if number is less than one or a multiple of two
    else if (number <= 1 || number % 2 == 0)
    {
        return false;
    }
    else
    {
        //iterates through all numbers from 3 to just before the number
        for (int j = 3; j < number; j++)
        {
            //returns false if number is divisible by j
            if (number%j == 0)
            {
                return false;
            }
        }
        return true;
    }
}