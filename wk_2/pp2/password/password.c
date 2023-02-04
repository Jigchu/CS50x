#include <ctype.h>
#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    //gets password and checks if valid with valid function
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(string password)
{
    //set requirements to false
    bool digit = false;
    bool lower = false;
    bool upper = false;
    bool special = false;

    long length = strlen(password);

    //iterates through passsword and checks for each requirement
    for (int i = 0; i < length; i++)
    {
        char c = password[i];

        //checks if it is a num, letter or special char
        if (isdigit(c))
        {
            digit = true;
        }
        else if (isalpha(c))
        {
            if (isupper(c))
            {
                upper = true;
            }
            else
            {
                lower = true;
            }
        }
        else
        {
            if (isprint(c))
            {
                special = true;
            }
        }
    }

    //checks if password has all requirements
    if (special && upper && lower && digit)
    {
        return true;
    }
    return false;
}
