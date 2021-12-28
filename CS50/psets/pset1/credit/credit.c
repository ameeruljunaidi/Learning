#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get input from user
    long cc_number = get_long("Number: ");

    // Get length of cc
    int cc_length = 0;
    long cc_length_check = cc_number;
    do
    {
        cc_length_check /= 10;
        cc_length += 1;
    }
    while (cc_length_check > 0);

    // Declare result of mod & and initialize values
    // Counter will be used to check if even or not
    long cc_digit_check = cc_number;
    int digit_selected;
    int valid_check = 0;
    int starting_digits;
    int starting_digits_first;
    int starting_digits_second;
    int pos_check = 1;

    // For debugging
    printf("odd_pos | digit_selected | valid_check | pos_check | cc_digit_check\n");

    for (int i = cc_length; i >= 0; i--)
    {
        // Check if position is odd or even (return true if odd)
        bool odd_pos = pos_check % 2 == 1;

        // Get result of mod based on position
        digit_selected = cc_digit_check % 10;

        // If odd, add number, if even, multiply and just add the digits
        if (odd_pos)
        {
            // Since odd, just add the mod results
            valid_check += digit_selected;
        }
        else
        {
            // Since even, need to multiply first
            int mod_odd = digit_selected;
            mod_odd *= 2;

            // Get all the digits and add it to the valid_check variable
            do
            {
                // Get the last digit
                int prod_digits = mod_odd % 10;

                // Add it to valid_check
                valid_check += prod_digits;

                // Remove the last digit
                mod_odd /= 10;
            }
            while (mod_odd > 0);

        }

        // Based on card lenth, get starting digits
        if (i == 2)
        {
            starting_digits_second = digit_selected;
        }
        if (i == 1)
        {
            starting_digits_first = digit_selected;
        }

        // Preview to make sure it works
        printf("%i | ", odd_pos);
        printf("%i | ", digit_selected);
        printf("%i | ", valid_check);
        printf("%i | ", pos_check);
        printf("%li | \n", cc_digit_check);

        // Go to next position and truncate the last digit
        cc_digit_check /= 10;
        pos_check++;
    }

    // Perform checks
    // Amex: 1, MasterCard: 2, Visa: 3
    int checksum;
    int checklength;
    int checkstart;

    switch (valid_check % 10)
    {
        case 0:
            checksum = 1;
            break;

        default:
            checksum = 0;
    }

    switch (cc_length)
    {
        case 15:
            checklength = 1;
            break;

        case 16:
            checklength = 4;
            break;

        case 13:
            checklength = 3;
            break;

        default:
            checklength = 0;
    }

    // Get starting digits depending on card
    if ((checklength > 2) && (starting_digits_first == 4))
    {
        starting_digits = starting_digits_first;
        checklength = 3;
    }
    else if ((checklength > 2) && (starting_digits_first > 4))
    {
        starting_digits = starting_digits_first * 10 + starting_digits_second;
        checklength = 2;
    }
    else
    {
        starting_digits = starting_digits_first * 10 + starting_digits_second;
    }

    switch (starting_digits)
    {
        case 34:
        case 37:
            checkstart = 1;
            break;

        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            checkstart = 2;
            break;

        case 4:
            checkstart = 3;
            break;

        default:
            checkstart = 0;
    }

    // Check values
    printf("valid_check: %i\n", valid_check);
    printf("card_length: %i\n", cc_length);
    printf("starting_digits_first: %i\n", starting_digits_first);
    printf("starting_digits_second: %i\n", starting_digits_second);
    printf("starting_digits: %i\n", starting_digits);
    printf("checksum: %i\n", checksum);
    printf("checklength: %i\n", checklength);
    printf("checkstart: %i\n", checkstart);

    // Print card type
    switch (checksum * checklength * checkstart)
    {
        case 1:
            printf("AMEX\n");
            break;

        case 4:
            printf("MASTERCARD\n");
            break;

        case 9:
            printf("VISA\n");
            break;

        case 0:
            printf("INVALID\n");
            break;

        default:
            printf("ERROR\n");
    }

    // American Express
    // Num of digits: 15
    // Starting with: 34 or 37

    // MasterCard
    // Num of digits: 16
    // Starting with: 51, 52, 53, 54, or 55

    // Visa
    // Number of digits: 13 or 16
    // Starting with with: 4
}

