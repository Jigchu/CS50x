#include <cs50.h>
#include <stdio.h>

long calc_years(long start_s, long end_s);

int main(void)
{
    //Prompt for start size
    long start;
    do
    {
        start = get_long("Start size:");
    }
    while (start < 9);
    //Prompt for end size
    long end;
    do
    {
        end = get_long("End size:");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    long years = calc_years(start, end);
    //Print number of years
    printf("Years: %li\n", years);
}

long calc_years(long start_s, long end_s)
{
    long year = 0;
    long curr_pop = start_s;

    //calculates population each year till end size is reached
    while (curr_pop < end_s)
    {
        long birth = curr_pop / 3;
        long death = curr_pop / 4;
        curr_pop = curr_pop + birth - death;
        year++;
    }

    return year;
}