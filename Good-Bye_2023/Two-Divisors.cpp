#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        if (b % a == 0)
        {
            cout << b * (b / a) << endl;
        }
        else
            cout << b * (a / __gcd(a, b)) << endl;
    }
}