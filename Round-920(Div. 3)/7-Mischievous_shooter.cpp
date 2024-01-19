

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

vector<string> rot(const vector<string> &a)
{
    const int n = a.size(), m = a[0].size();
    vector<string> res(m, string(n, ')'));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            res[j][i] = a[i][m - 1 - j];
        }
    }
    return res;
}

int f(const vector<string> &a, int k)
{
    k += 1;
    const int n = a.size(), m = a[0].size();
    vector<vector<int>> left(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            left[i][j] = (a[i][j] == '#');
            if (j)
            {
                left[i][j] += left[i][j - 1];
            }
        }
    }
    auto subrect = left;
    auto lin = left;
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            subrect[i][j] += subrect[i - 1][j];
            if (j)
            {
                lin[i][j] += lin[i - 1][j - 1];
            }
        }
    }

    auto getlin = [&](int i, int j)
    {
        assert(i < n);
        if (i < 0 || j < 0)
        {
            return 0;
        }
        if (j < m)
        {
            return lin[i][j];
        }
        if (j - i >= m - 1)
        {
            return subrect[i][m - 1];
        }
        return subrect[i][m - 1] - subrect[i - (j - (m - 1))][m - 1] + lin[i - (j - (m - 1))][m - 1];
    };

    auto getsubrect = [&](int i, int j)
    {
        assert(i < n);
        if (i < 0 || j < 0)
        {
            return 0;
        }
        return subrect[i][min(j, m - 1)];
    };

    auto h = [&](int i, int j)
    {
        return getlin(i, j + k - 1) - getlin(i - k, j - 1) - getsubrect(i, j - 1) + getsubrect(i - k, j - 1);
    };

    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            res = max(res, h(i, j));
        }
    }
    return res;
}

void solve()
{
    [[maybe_unused]] int n = nxt(), m = nxt(), k = nxt();
    vector<string> field(n);
    for (auto &s : field)
    {
        cin >> s;
    }
    int ans = 0;
    for (int it = 0; it < 4; ++it)
    {
        ans = max(ans, f(field, k));
        field = rot(field);
    }
    cout << ans << "\n";
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