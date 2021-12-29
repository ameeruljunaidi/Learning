#include <bits/stdc++.h>

using namespace std;

void PrintArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << ' ';
    }
    cout << '\n';
}

void Merge(int array[], int const left, int const mid, int const right)
{
    // Merge the two sorted aub-arrays, first is array[begin, mid] and second is array[mid, end]

    // Get the size of the sub-arrays
    auto const firstSubArraySize = mid - left + 1;
    auto const secondSubArraySize = right - mid;

    // Create a temp array and copy over the elements into the temp arrays
    int *leftArray = new int[firstSubArraySize];
    int *rightArray = new int[secondSubArraySize];

    for (int i = 0; i < firstSubArraySize; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < secondSubArraySize; j++)
        rightArray[j] = array[mid + 1 + j];

    // size_t leftArraySize = sizeof(&leftArray) / sizeof(leftArray[0]);
    // size_t rightArraySize = sizeof(&rightArray) / sizeof(rightArray[0]);
    //
    // cout << "Left Array: ";
    // PrintArray(leftArray, static_cast<int>(leftArraySize));
    // cout << "Right Array: ";
    // PrintArray(rightArray, static_cast<int>(rightArraySize));

    // Initialize the indices for first and second sub-array
    auto firstSubArrayIndex = 0;
    auto secondSubArrayIndex = 0;
    int mergedArrayIndex = left;

    // Merge the temp array back into array[left...right]
    // Run the loop while the indices of the subarray is less than the size of the sub-arrays
    while (firstSubArrayIndex < firstSubArraySize && secondSubArrayIndex < secondSubArraySize)
    {
        if (leftArray[firstSubArrayIndex] <= rightArray[secondSubArrayIndex])
        {
            array[mergedArrayIndex] = leftArray[firstSubArrayIndex];
            firstSubArrayIndex++;
        }
        else
        {
            array[mergedArrayIndex] = rightArray[secondSubArrayIndex];
            secondSubArrayIndex++;
        }
        mergedArrayIndex++;
    }

    // There might be some element still left out
    while (firstSubArrayIndex < firstSubArraySize)
    {
        array[mergedArrayIndex] = leftArray[firstSubArrayIndex];
        firstSubArrayIndex++;
        mergedArrayIndex++;
    }

    while (secondSubArrayIndex < secondSubArraySize)
    {
        array[mergedArrayIndex] = rightArray[secondSubArraySize];
        secondSubArrayIndex++;
        mergedArrayIndex++;
    }
}

void MergeSortRecursive(int array[], int const begin, int const end) // NOLINT(Misc-no-recursion)
{
    // The base case is when the beginning index and the end index crosses
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;    // Get the middle index of the array
    MergeSortRecursive(array, begin, mid);   // Recursively call sort from start to middle
    MergeSortRecursive(array, mid + 1, end); // Recursively call to sort from middle to end
    Merge(array, begin, mid, end);           // Merge the two sorted arrays
}

[[maybe_unused]] void MergeSort()
{
    cout << "Merge Sort" << '\n';
    // This algorithm has O(n log n) time complexity
    //
    // 1. If a = b, do not do anything, because the subarray is already sorted
    // 2. Calculate the position of the middle element: k = (a+b)/2
    // 3. Recursively sort the subarray array[a...k]
    // 4. Recursively sort the subarray array[k+1...b]
    // 5. Merge the sorted sub-arrays array[a...k] and array [k+1...b] into a sorted subarray array[a...b]
    //
    // This halves the subarray at each step, the recursion consists of O(log n) levels
    // Processing each levels take O(n) of time though (merging is possible in liner time since already sorted)

    const int n = 6;
    int array[n] = {12, 11, 13, 5, 6, 7};

    cout << "Before: ";
    PrintArray(array, n);

    // Pass in the array, the first index and the last index of the array
    MergeSortRecursive(array, 0, n - 1);

    cout << "After: ";
    PrintArray(array, n);
}

[[maybe_unused]] void BubbleSort()
{
    cout << "Bubble Sort" << '\n';
    // Elements "bubble" in the array according their values
    // This has a time complexity of O(n^2)
    // this algorithm is short and consist of two nested loops

    const int n = 8;
    int array[8] = {1, 3, 8, 2, 9, 2, 5, 6};

    cout << "Before: ";
    PrintArray(array, n);

    // Sort the array
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                swap(array[j], array[j + 1]);
            }
        }
    }

    cout << "After: ";
    PrintArray(array, n);
}

int main()
{
    // Efficient sorting algorithm work in O(n log n) time complexity
    // Other algorithms that uses a sorting subroutine also has this time complexity

    // BubbleSort();
    MergeSort();

    return 0;
}