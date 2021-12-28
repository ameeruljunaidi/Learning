#include <bits/stdc++.h>

using namespace std;

void printArray(int array[], size_t arraySize)
{
   for (size_t i = 0; i < arraySize; i++)
   {
       cout << array[i] << " ";
   }

   cout << '\n';
}

int main()
{
    int testArray[] = {4, 3, 5, 4, 1, 4, 2};
    size_t testArraySize = sizeof(testArray) / sizeof (testArray[0]);
    printArray(testArray, testArraySize);

    sort(testArray, testArray+testArraySize);
    printArray(testArray, testArraySize);

    auto lowerBound = lower_bound(testArray, testArray+testArraySize, 4);
    auto upperBound = upper_bound(testArray, testArray+testArraySize, 4);

    cout << "Lower bound is: " << lowerBound - testArray << '\n';
    cout << "Upper bound is: " << upperBound - testArray << '\n';

    return 0;
}