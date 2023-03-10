#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Var to print winner
    int winner;

    if (score1 > score2)
    {
        winner = 1;
    }
    else if (score2 > score1)
    {
        winner = 2;
    }
    else
    {
        winner = 0;
    }

    if (winner == 0)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player %i wins\n", winner);
    }
}

int compute_score(string word)
{
    long length = strlen(word);
    int score = 0;

    //iterates through string to calculate points
    for (int i = 0; i < length; i++)
    {
        char c = word[i];

        //checks if char is a letter
        if (isalpha(c))
        {
            //make c uppercase for ease of computing
            c = toupper(c);
            int index = c - 65;
            score += POINTS[index];
        }
        else
        {
            continue;
        }
    }

    return score;

}
