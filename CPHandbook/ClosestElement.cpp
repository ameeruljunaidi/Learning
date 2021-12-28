#include <bits/stdc++.h>
using namespace std;

int main()
{
    // This only concerns set - finding the closest element to a value x

    set<int> s = {1, 8, 5, 5, 5, 6, 7, 8, 9, 10};
    const int x = 5;

    auto it = s.lower_bound(x); // This returns an iterator to the smallest element in the set whose value is at least x
    if (it == s.begin())
    {
        cout << *it << '\n';
    }
    else if (it == s.end())
    {
        it--;
        cout << *it << '\n';
    }
    else
    {
        int a = *it;
        it--;
        int b = *it;

        if (x - b < a - x)
            cout << b << '\n';
        else
            cout << a << '\n';
    }

    return 0;
}