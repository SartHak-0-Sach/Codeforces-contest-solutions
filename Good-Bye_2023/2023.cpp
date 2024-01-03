#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int k;
        cin >> k;
        int b[n];
        long long product = 1;
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
            product *= b[i];
        }
        if (2023 % product == 0)
        {
            cout << "YES" << endl;
            for (int i = 0; i < k - 1; i++)
            {
                cout << "1 ";
            }
            cout << 2023 / product << endl;
        }

        else
            cout << "NO" << endl;
    }
    return 0;
}