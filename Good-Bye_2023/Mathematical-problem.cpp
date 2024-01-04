#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int N;
    cin >> N;
    if (N == 1)
    {
        cout << 1 << '\n';
        return;
    }
    else
    {
        vector<string> s;
        for (int b = 1; 2 * b < N; b++)
        {
            s.push_back("1" + string(b - 1, '0') + "6" + string(b - 1, '0') + "9" + string(N - 2 * b - 1, '0'));
            s.push_back("9" + string(b - 1, '0') + "6" + string(b - 1, '0') + "1" + string(N - 2 * b - 1, '0'));
        }
        s.push_back("196" + string(N - 3, '0'));
        s.resize(N);
        for (string x : s)
            cout << x << '\n';
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