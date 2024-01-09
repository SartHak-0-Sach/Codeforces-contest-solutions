#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int size;
        cin >> size;
        char a;
        int ans = 0;
        for (int i = 0; i < size; i++)
        {
            cin >> a;
            if (a == '+')
                ans++;
            else
                ans--;
        }
        if (ans < 0)
        {
            ans *= -1;
        }
        cout << ans << endl;
    }
    return 0;
}