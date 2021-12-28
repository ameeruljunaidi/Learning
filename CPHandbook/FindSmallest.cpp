#include <bits/stdc++.h>

using namespace std;

bool ok(int x)
{
    if (x < 50)
    {
        return false;
    }

    return true;
}

int main()
{
    // This finds the smallest x that returns true
    // We know it's 5 since it's obvious from the function ok() above, but pretend we don't know

    // x is where we first start, set at -1 to represent invalid out-of-scope number
    // z ia a number large enough that we know is true
    int x = -1, z = numeric_limits<int>::max();

    for (int b = z; b >= 1; b /= 2)
    {
        while (!ok(x + b)) x+= b;
    }

    int k = x + 1;

    cout << "Answer: " << k << '\n';

    return 0;
}