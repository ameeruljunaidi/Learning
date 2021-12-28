#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        // Prompt user for height
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Draw the pyramids
    for (int i = 0; i < height; i++)
    {
        // Print spaces depending on height
        for (int j = height - i - 1; j > 0; j--)
        {
            printf(" ");
        }

        // Print # depending on height (left side)
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        // Print the two whitespaces
        printf("  ");

        // Print # depending on height (right side)
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        // New line
        printf("\n");
    }
}