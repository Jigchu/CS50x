#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    //Gets weeks && hours per week
    int weeks = get_int("Numbers of weeks taking CS50: ");
    int hours[weeks];
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW hours: ", i);
    }
    //Gets char input from user and makes it uppercase
    char c = get_char("Enter T for total hours and A for average hours per week: ");
    c = toupper(c);
    int total_hours = 0;
    //Gets total hours
    for (int i = 0; i < weeks; i++)
    {
        total_hours += hours[i];
    }
    //Responds to query from input returns 1 if invalid input
    if (c == 'T')
    {
        printf("%i hours\n", total_hours);
    }
    else if (c == 'A')
    {
        printf("%.2f hours\n", total_hours / (float) weeks);
    }
    else
    {
        return 1;
    }
}