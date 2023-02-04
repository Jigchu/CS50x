#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

long get_letters(string t, long len);
long get_sentences(string t, long len);
long get_words(string t, long len);

int main(void)
{
    // Gets the text and its length
    string text = get_string("Text: ");
    long length = strlen(text);

    // Gets num of letters, sentences and words
    long letters = get_letters(text, length);
    long sentences = get_sentences(text, length);
    float words = get_words(text, length);

    // Calculates num of letters and sentences per 100 words
    double ave_letter = letters / words * 100.0;
    double ave_sentence = sentences / words * 100.0;

    // Calculates score
    double float_score = 0.0588 * ave_letter - 0.296 * ave_sentence - 15.8;
    int score = round(float_score);

    // Checks if score is above 16 / below 1 and prints grade
    if (score > 16)
    {
        printf("Grade 16+\n");
    }
    else if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", score);
    }
}

long get_letters(string t, long len)
{
    // Initialise count var
    long count = 0;

    // Iterates through string and if char is alphabetical, count++
    for (long i = 0; i < len; i++)
    {
        if (isalpha(t[i]))
        {
            count ++;
        }
    }

    return count;
}

long get_sentences(string t, long len)
{
    // Initialise count var
    long count = 0;

    // Initialise flag used to check whether its the beginning of a sentence
    bool flag = false;

    // Iterate through string
    for (int i = 0; i < len; i++)
    {
        // Checks if sentence has ended
        if (flag)
        {
            if (t[i] == 33 || t[i] == 46 || t[i] == 63)
            {
                flag = false;
            }
        }
        // Checks if sentence has started
        else if (!flag)
        {
            if (isalpha(t[i]))
            {
                flag = true;
                count ++;
            }
        }
    }

    return count;
}

long get_words(string t, long len)
{
    // Initialise count var
    long count = 0;

    // Initialise flag used to check the start of the word
    bool flag = false;

    // Iterates through the string
    for (int i = 0; i < len; i++)
    {
        // Checks for end of word
        if (flag)
        {
            if (isspace(t[i]))
            {
                flag = false;
            }
        }
        // Checks for start of word
        else if (!flag)
        {
            if (isalpha(t[i]))
            {
                flag = true;
                count++;
            }
        }
    }

    return count;
}