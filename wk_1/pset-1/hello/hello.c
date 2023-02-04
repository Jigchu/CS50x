#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //gets name
    string name = get_string("What is your name?\n");
    //print hello, [name]
    printf("hello, %s\n", name);
}