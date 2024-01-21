#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
using LL = long long;

int main()
{

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        vector<LL> s1(n + 1), s2(n + 1);
        s1[2] = 1;
        for (int i = 3; i <= n; i++)
        {
            s1[i] = s1[i - 1];
            if (a[i] - a[i - 1] < a[i - 1] - a[i - 2])
            {
                s1[i] += 1;
            }
            else
            {
                s1[i] += a[i] - a[i - 1];
            }
        }
        s2[n - 1] = 1;
        for (int i = n - 2; i >= 1; i--)
        {
            s2[i] = s2[i + 1];
            if (a[i + 1] - a[i] < a[i + 2] - a[i + 1])
            {
                s2[i] += 1;
            }
            else
            {
                s2[i] += a[i + 1] - a[i];
            }
        }
        int m;
        cin >> m;
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            if (x < y)
            {
                cout << s1[y] - s1[x] << '\n';
            }
            else
            {
                cout << s2[y] - s2[x] << '\n';
            }
        }
    }
}