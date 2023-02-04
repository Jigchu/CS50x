#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // Checks if string is empty
    if (!input[0])
    {
        return 0;
    }

    // Gets strlen
    int len = strlen(input);

    // Gets the last char of str
    char c = input[len - 1];

    // Removes last char of str
    input[len - 1] = '\0';

    // Calls itself with new input and saves the output in a var
    int num = convert(input);

    // Converts char to int and adds to num
    int i = c - '0';
    num *= 10;
    num += i;

    return num;
}