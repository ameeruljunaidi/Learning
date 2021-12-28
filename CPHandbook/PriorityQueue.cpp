#include <bits/stdc++.h>
using namespace std;

// Operates like a queue but each element has a certain priority, determined by the order in which elements are removed
// Only supports comparable data (data in the queue must be able to be ordered somehow)
// It doesn't re-sort the elements every time whenever it pops an element from the top, it stores the data in a heap
//
// There two different types, max heap and min heap
// 1. Max heap's parents are all bigger than its children
// 2. Min heaps parents are all smaller than its children

int main()
{
    // Priority queue in the STL library sorts the data in decreasing order by default
    // This is also known as a min PQ, which uses a min heap
    priority_queue<int> aq;
    aq.push(3);
    aq.push(5);
    aq.push(7);
    aq.push(2);
    cout << aq.top() << '\n'; // 7, because it is the largest
    aq.pop();
    cout << aq.top() << '\n'; // 5, because it is now the largest
    aq.pop();
    aq.push(6);
    cout << aq.top() << '\n'; // 6, because it is now the largest

    // To get a PQ that is a max PQ
    priority_queue<int, vector<int>, greater<>> bq;
    bq.push(3);
    bq.push(5);
    bq.push(7);
    bq.push(2);
    cout << bq.top() << '\n';

    return 0;
}