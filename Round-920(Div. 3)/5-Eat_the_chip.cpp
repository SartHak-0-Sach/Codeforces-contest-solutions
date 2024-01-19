#include <bits/stdc++.h>

#define itn int
#define all(x) (x).begin(), (x).end()
#define make_unique(x) \
    sort(all((x)));    \
    (x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt()
{
    int x;
    cin >> x;
    return x;
}

void solve()
{
    int h = nxt(), w = nxt();
    int xa = nxt(), ya = nxt();
    int xb = nxt(), yb = nxt();
    if (xa >= xb)
    {
        cout << "Draw\n";
        return;
    }
    const bool alice_hunter = (xb - xa) % 2;
    const int alice_moves = (xb - xa + 1) / 2;
    const int bob_moves = (xb - xa) / 2;
    if ((ya < yb) == alice_hunter)
    {
        ya = w + 1 - ya;
        yb = w + 1 - yb;
    }
    ya = max(1, ya - alice_moves);
    yb = max(1, yb - bob_moves);
    if (alice_hunter)
    {
        cout << (ya <= yb ? "Alice" : "Draw") << "\n";
    }
    else
    {
        cout << (yb <= ya ? "Bob" : "Draw") << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = nxt();
    while (t--)
    {
        solve();
    }

    return 0;
}