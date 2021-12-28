#include <bits/stdc++.h>
using namespace std;

void methodOne()
{
    // Each step halves the size of the search region
    // Each step check the middle element of the active region, if it is the target element, search terminates
    // Otherwise, search recursively to the left or right half of the region, depending on middle of the element

    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n = sizeof(array) / sizeof(array[0]);

    // Variable 'a' is the start index of the search space
    // Variable 'b' is the last index of the array
    // Variable 'x' is the number to look for
    int a = 0, b = static_cast<int>(n) - 1, x = 4;
    while (a <= b) // While start index is less than or equal to end index
    {
        int k = (a + b) / 2; // Variable 'k' is the middle index of the search space

        if (array[k] == x) // If element in the middle of the search space is the answer
        {
            cout << "Element " << x << " found at index " << k << '\n';
        }

        // When element is not found, check if the middle element is bigger or smaller
        if (array[k] > x) // If the index in the middle is bigger, then want to get rid of the right half
            b = k - 1;    // Set the end index of the search space to be the middle index - 1
        else              // If the index in the middle is smaller, then want to get rid of the left index
            a = k + 1;    // Set the start index of the search space to be the middle index + x
    }
}

void methodTwo()
{
    // Method two is a bit confusing to me - it iterates through the elements of the array
    // make jumps and slow the speed when we get close to the target element
    // Initial jump length is n/2, then n/4, n/8, n/16, etc. until the length is finally 1
    // After the jumps, either the target element has been found or we know it doesn't exist in the array

    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t n = sizeof(array) / sizeof(array[0]);

    // Variable 'k' is the start index of the search space
    // Variable 'x' is the number that we are looking for
    int k = 0, x = 9;

    // The variable 'b' is the index that is initialized to the middle of the search space
    // The loop goes on while b is >= 1
    // Every iteration b gets halved by 2
    for (int b = static_cast<int>(n) / 2; b >= 1; b /= 2)
    {
        // Inner loop runs while:
        // 1. k + b is still a valid index in the search space
        // 2. The element at k + b is equal to or less than x
        while (k + b < n && array[k + b] <= x)
            k += b; // Variable 'k' only gets updated if the element at k + b is equal to or less than x
    }

    if (array[k] == x)
    {
        cout << "Element " << x << " found at index " << k << '\n';
    }
    else
    {
        cout << "Element not found" << '\n';
    }
}

int main()
{
    methodOne();
    methodTwo();

    return 0;
}