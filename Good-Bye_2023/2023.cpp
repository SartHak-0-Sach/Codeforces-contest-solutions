#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int N, K;
    cin >> N >> K;
    int A = 2023;
    for (int i = 0; i < N; i++)
    {
        int b;
        cin >> b;
        if (A % b == 0)
        {
            A /= b;
        }
        else
        {
            A = 0;
        }
    }
    if (A)
    {
        cout << "YES" << '\n';
        cout << A;
        for (int i = 1; i < K; i++)
        {
            cout << " 1";
        }
        cout << '\n';
    }
    else
    {
        cout << "NO" << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
}