#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);

    // Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach threshold
    int n = start_size;
    int years = 0;
    while (n < end_size)
    {
        int n_born = n / 3;
        int n_pass = n / 4;
        int n_net = n_born - n_pass;

        n += n_net;
        years++;
    };

    // Print number of years
    printf("Years: %i\n", years);
}