#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int validate_key(string argv[]);
void enchipher(string argv[], string plaintext);
int check_alpha(string key);
int check_repeat(string key);

int main(int argc, string argv[])
{
    // Validate key
    int exit_code = validate_key(argv);

    // Get plaintext
    string plaintext = get_string("plaintext: ");

    // Enchipher
    enchipher(argv, plaintext);

    return exit_code;
}

int validate_key(string argv[])
{
    // Check key length
    // Check for non-alphabetic characters
    // Check for repeated characters

    // Get key
    string key = argv[1];
    int key_length;

    // Get errors
    int key_error = key == 0 || argv[2] > 0;
    int length_error = 0;
    int alpha_error = 0;
    int repeat_error = 0;

    int error_key = 0;
    string usage_error_message = "Usage: ./substitution key";
    string length_error_message = "Key must contain 26 characters.";
    string alpha_error_message = "Key must only contain alphabetic characters.";
    string repeat_error_message = "Key must not contain repeated characters.";

    if (key_error)
    {
        printf("%s\n", usage_error_message);
        error_key += 1;
    }
    else
    {
        key_length = strlen(key);
        length_error = key_length != 26;
        alpha_error = check_alpha(key);
        repeat_error = check_repeat(key);
    }

    if (length_error)
    {
        printf("%s\n", length_error_message);
        error_key += 2;
    }

    if (alpha_error)
    {
        printf("%s\n", alpha_error_message);
        error_key += 4;
    }

    if (repeat_error)
    {
        printf("%s\n", repeat_error_message);
        error_key += 8;
    }

    if (error_key > 0)
    {
        exit(1);
    }

    return 0;
}

int check_alpha(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        int check = isalpha(key[i]);
        if (check == 0)
        {
            return 1;
        }
    }
    return 0;
}

int check_repeat(string key)
{
    int key_length = strlen(key);

    for (int i = 0; i < key_length; i++)
    {
        int same_char = 0;

        for (int j = 0; j < key_length; j++)
        {
            if (key[i] == key[j])
            {
                same_char++;
            }
        }

        if (same_char > 1)
        {
            return 1;
        }
    }
    return 0;
}

void enchipher(string argv[], string plaintext)
{
    // For each letter, determine what it maps to
    // The mapping is based on the position of the letter in the alphabet
    // Preserve case
    // Leave non-alphabetic characters as is

    int text_length = strlen(plaintext);
    char deciphered_text[text_length];
    string key = argv[1];

    for (int i = 0; i < text_length; i++)
    {
        char character = plaintext[i];
        int deciphered_char_loc;

        if (isalpha(character))
        {
            if (islower(character))
            {
                deciphered_char_loc = character - 97;
                deciphered_text[i] = tolower(key[deciphered_char_loc]);
            }
            else
            {
                deciphered_char_loc = character - 65;
                deciphered_text[i] = toupper(key[deciphered_char_loc]);
            }
        }
        else
        {
            deciphered_text[i] = character;
        }
    }

    deciphered_text[text_length] = '\0';
    string return_string = (string)deciphered_text;
    printf("ciphertext: %s\n", deciphered_text);
}