#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    //Prints error message and return 1 when invalid cmdline arg
    if (argc < 2 || argc > 2)
    {
        printf("Invalid number of command-line arguments\n");
        return 1;
    }
    //Gets word and puts it through function to replace all vowel then prints it
    string word = argv[1];
    word = replace(word);
    printf("%s\n", word);
}

string replace(string s)
{
    long length = strlen(s);
    //iterates through string and replaces each vowel with correct number
    for (int i = 0; i < length; i++)
    {
        switch (s[i])
        {
            case 'a':
                s[i] = '6';
                break;

            case 'e':
                s[i] = '3';
                break;

            case 'i':
                s[i] = '1';
                break;

            case 'o':
                s[i] = '0';
                break;
        }
    }

    return s;
}