#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;

int main()
{
    indexed_set s;
    s.insert(2);
    s.insert(3);
    s.insert(7);
    s.insert(9);

    // With this set we can have access to the indices that the elements would have in a sorted array
    // find_by_order returns an iterator to the element at a given position

    auto x = s.find_by_order(2);
    cout << *x << '\n'; // 7

    // order_of_key returns the position of a given element
    // If the element doesn't exist, then it would return the position that element would have in the set

    cout <<  s.order_of_key(7) << '\n';
    cout <<  s.order_of_key(6) << '\n';
    cout <<  s.order_of_key(8) << '\n';

    return 0;
}
