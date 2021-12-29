#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for user's name
    string name = get_string("What is your name?\n");

    // Print the name with hello
    printf("hello, %s\n", name);
}