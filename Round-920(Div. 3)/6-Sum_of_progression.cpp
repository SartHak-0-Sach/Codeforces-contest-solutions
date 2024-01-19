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

struct Query
{
    int s, d;
    int k;
    int id;

    bool operator<(const Query &ot) const
    {
        return d < ot.d;
    }
};

void solve()
{
    int n = nxt(), q = nxt();
    vector<int> a(n);
    generate(all(a), nxt);
    vector<long long> sum_free(n), sum_lin(n);
    vector<Query> qrs(q);
    for (int i = 0; i < q; ++i)
    {
        qrs[i].id = i;
        qrs[i].s = nxt() - 1;
        qrs[i].d = nxt();
        qrs[i].k = nxt();
    }
    sort(all(qrs));
    vector<long long> ans(q);
    int last = 0;

    auto prepare = [&](int d)
    {
        last = d;
        for (int i = n - 1; i >= 0; --i)
        {
            sum_free[i] = sum_lin[i] = a[i];
            if (i + d < n)
            {
                sum_free[i] += sum_free[i + d];
                sum_lin[i] += sum_lin[i + d] + sum_free[i + d];
            }
        }
    };

    for (const auto &qr : qrs)
    {
        if (qr.k <= qr.d)
        {
            long long res = 0;
            for (int i = 0; i < qr.k; ++i)
            {
                res += 1ll * a[qr.s + qr.d * i] * (i + 1);
            }
            ans[qr.id] = res;
        }
        else
        {
            if (qr.d != last)
            {
                prepare(qr.d);
            }
            long long res = sum_lin[qr.s];
            if (qr.s + qr.d * qr.k < n)
            {
                res -= sum_lin[qr.s + qr.d * qr.k];
                res -= sum_free[qr.s + qr.d * qr.k] * qr.k;
            }
            ans[qr.id] = res;
        }
    }
    for (auto x : ans)
    {
        cout << x << " ";
    }
    cout << "\n";
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