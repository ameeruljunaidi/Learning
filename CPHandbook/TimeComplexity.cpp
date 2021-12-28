#include <bits/stdc++.h>

using namespace std;

int MinSubarraySum(int algorithm)
{
    // Returns the largest possible sum of a sequence of consequtive values in the array
    const size_t n = 8;
    int array[n] = {-1, 2, 4, -3, 5, 2, -5, 2};

    if (algorithm == 1)
    {
        // Algorithm 1 is naive, go through all possible subararys
        // In this case the time complexity is O(3)

        int best = 0; // Keep track of the best possible sum

        for (int a = 0; a < n; a++) // Loop through the array's index
        {
            for (int b = a; b < n; b++) // This loop goes through the indices after the current index
            {
                int sum = 0; // At the current index, keep track of the sum
                             // The sum would be reset every time the main index moves

                for (int k = a; k <= b; k++) // This loop goes through the indices before the current index
                {
                    sum += array[k]; // Add the current value at index to the sume
                }
                best = max(best, sum); // Update the best variable and here sum will be reset
            }
        }

        return best;
    }

    if (algorithm == 2)
    {
        // Algorithm 2 removes one loop from it, making it O(2)
        int best = 0;

        for (int a = 0; a < n; a++)
        {
            int sum = 0;

            for (int b = a; b < n; b++)
            {
                sum += array[b];
                best = max(best, sum);
            }
        }

        return best;
    }

    if (algorithm == 3)
    {
        // This algorithm allows us to solve this in O(n) time
        // Calculate, for each array position, the maximum sum of a subarray that ens at that position

        int best = 0, sum = 0;
        for (int k = 0; k < n; k++)
        {
            sum = max(array[k], sum + array[k]);
            best = max(best, sum);
        }

        return best;
    }

    return 0;
}

int main(void)
{
    cout << MinSubarraySum(3) << '\n';

    return 0;
}
