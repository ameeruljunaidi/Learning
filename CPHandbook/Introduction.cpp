#include <bits/stdc++.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define FOR(i, a, b) for (int i = a; i <= b; i++)

using std::cout;

void factorial_modulo(int n, int m)
{
    // calculates n! modulo m

    long long x = 1;

    for (int i = 2; i <= n; i++)
    {
        x = (x * i) % m;
    }

    cout << x % m << "\n";

    /*
        if the number could be negative, need to mod first and add m

        x = x % m;
        if (x < 0) x += m;

        only need to do this if there is subtractions and the number could be negative
    */
}

void compare_floating_point()
{
    double x = 0.3 * 3 + 0.1;
    printf("%.20f\n", x); // this prints up to 20 decimal points, the answer is wrong though

    /*
        when comparing two floating points, usually you want to compare it with very small number
        if (abs(a - b) < 1e-9) {
            ...
        }
    */
}

int main(void)
{
    // factorial_modulo(4, 1);
    compare_floating_point();

    return 0;
}