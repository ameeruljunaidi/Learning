#include <bits/stdc++.h>

using namespace std;

struct P
{
    int x, y;

    P(int i, int j) : x(i), y(j)
    {
    }

    bool operator<(const P &p) const
    {
        if (x != p.x)
            return x < p.x;
        else
            return y < p.y;
    }
};

struct Q
{
    int x, y;

    Q(int i, int j) : x(i), y(j)
    {
    }
};

void structSort()
{

    vector<P> testVector{};
    testVector.emplace_back(1, 2);
    testVector.emplace_back(4, 5);
    testVector.emplace_back(4, 2);
    testVector.emplace_back(4, 4);
    testVector.emplace_back(3, 5);
    testVector.emplace_back(5, 5);

    sort(testVector.begin(), testVector.end());

    for (const P current : testVector)
    {
        cout << current.x << ' ';
    }
    cout << '\n';
    for (const P current : testVector)
    {
        cout << current.y << ' ';
    }
    cout << '\n';
}

void lambdaSort()
{
    vector<Q> testVector{};
    testVector.emplace_back(1, 2);
    testVector.emplace_back(4, 5);
    testVector.emplace_back(4, 2);
    testVector.emplace_back(4, 4);
    testVector.emplace_back(3, 5);
    testVector.emplace_back(5, 5);

    sort(testVector.begin(), testVector.end(), [](const Q &left, const Q &right) {
        if (left.x != right.x)
        {
            return left.x < right.x;
        }
        else
        {
            return left.y < right.y;
        }
    });

    for (const Q current : testVector)
    {
        cout << current.x << ' ';
    }
    cout << '\n';
    for (const Q current : testVector)
    {
        cout << current.y << ' ';
    }
    cout << '\n';
}

int main()
{
    structSort();
    lambdaSort();

    return 0;
}