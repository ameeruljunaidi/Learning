#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Prompt the user for text
    string text = get_string("Text: ");

    // Count letters shouldn’t include any punctuation, digits, or other symbols
    // Use islpha() to check if it is a letter
    // Count space to determine number of words
    // Use isblank() to check if it is a space
    // Count punctuations to determine number of sentences
    // Can't use ispunct() to check if it is a punctuation point
    int letter_count = 0;
    int word_count = 1;
    int sentence_count = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Store the char to check in a variable
        char char_check = text[i];

        // Count letters, spaces, and punctuations
        if (isalpha(char_check) > 0)
        {
            letter_count++;
        }
        if (isblank(char_check) > 0)
        {
            word_count++;
        }
        if (char_check == '.' || char_check == '!' || char_check == '?')
        {
            sentence_count++;
        }
    }

    // Preview counts
    // printf("%i letter(s)\n", letter_count);
    // printf("%i word(s)\n", word_count);
    // printf("%i sentences(s)\n", sentence_count);

    // Get index = 0.0588 * L - 0.296 * S - 15.8
    float l = (float) letter_count / word_count * 100;
    float s = (float) sentence_count / word_count * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index > 0 && index < 17)
    {
        printf("Grade %i\n", index);
    }
}