#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

void solve()
{

    int n;
    cin >> n;

    int a[n];
    long long sum = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }

    int sq = sqrt(sum);

    if (1LL * sq * sq == sum)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

int main()
{
    int t = 1;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        solve();
    }
    
    return 0;
}