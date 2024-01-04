#include <bits/stdc++.h>
#include <numeric>
using namespace std;

using ll = int64_t;
void solve()
{
    ll A, B;
    cin >> A >> B;
    if (B % A == 0)
    {
        ll ans = B * (B / A);
        cout << ans << '\n';
    }
    else
    {
        ll ans = B * (A / __gcd(A, B));
        cout << ans << '\n';
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