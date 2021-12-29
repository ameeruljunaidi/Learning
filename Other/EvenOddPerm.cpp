#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::vector;
using std::string;

#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

bool isOddPermutation(vt<int> v)
{
    int moveCount = 0;
    for (int i = 0; i < sz(v); i++)
        moveCount += abs(v[i] - i);

    if (moveCount % 2 != 0)
        return true;

    return false;
}

int main()
{
    //           0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    vt<int> v = {0, 3, 2, 4, 5, 6, 7, 1, 9, 8};

    string answer = isOddPermutation(v) ? "Odd" : "Even";
    cout << answer << '\n';

    return 0;
}