#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi num, st;
vector<vector<pii>> ed;
int Time;
template <class F>
int dfs(int at, int par, F &f)
{
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at])
        if (pa.second != par)
        {
            tie(y, e) = pa;
            if (num[y])
            {
                top = min(top, num[y]);
                if (num[y] < me)
                    st.push_back(e);
            }
            else
            {
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up == me)
                {
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                }
                else if (up < me)
                    st.push_back(e);
                else
                {
                    f({e}); /* e is a bridge */
                }
            }
        }
    return top;
}

template <class F>
void bicomps(F f)
{
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

void solve()
{
    int N1, N2, M;
    cin >> N1 >> N2 >> M;
    vector<pair<int, int>> edges;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges.push_back({u, v});
    }
    auto [a, b] = edges[0];
    int N = N1 + N2;
    vector<int> label(N + 2);
    for (int i = 0; i < N; i++)
    {
        label[i] = i;
    }
    label[a] = N;
    N1--;
    while (N1 && N2)
    {
        for (int side : {0})
        {
            int v = N + side;
            vector<pair<int, int>> new_edges;
            for (auto [x, y] : edges)
            {
                x = label[x];
                y = label[y];
                if (x == y)
                    continue;
                if (x > y)
                    swap(x, y);
                new_edges.push_back({x, y});
            }
            sort(new_edges.begin(), new_edges.end());
            new_edges.resize(unique(new_edges.begin(), new_edges.end()) - new_edges.begin());
            // remove v. find a neighbor that is not w, is not an articulation point
            ed.assign(N + 2, {});
            int eid = 0;
            vector<int> can(N + 2, 0);
            vector<pair<int, int>> real_edges;
            for (auto [x, y] : new_edges)
            {
                if (x == v)
                {
                    can[y] = 1;
                }
                else if (y == v)
                {
                    can[x] = 1;
                }
                else
                {
                    ed[x].push_back({y, eid});
                    ed[y].push_back({x, eid});
                    eid++;
                    real_edges.push_back({x, y});
                }
            }
            vector<int> cnt(N + 2, 0);
            bicomps(
                [&](vector<int> es)
                {
                    set<int> seen;
                    for (int e : es)
                    {
                        auto [x, y] = real_edges[e];
                        seen.insert(x);
                        seen.insert(y);
                    }
                    for (int x : seen)
                        cnt[x]++;
                });
            int found = -1;
            for (int i = 0; i < N; i++)
            {
                if (can[i] && cnt[i] == 1)
                    found = i;
            }
            if (found >= 0)
            {
                label[found] = v;
                if (side == 0)
                {
                    N1--;
                }
                else
                {
                    N2--;
                }
                goto done;
            }
        }
        assert(false);
    done:;
    }
    for (int i = 0; i < N; i++)
    {
        if (label[i] == i)
        {
            if (N1)
            {
                N1--;
                label[i] = N;
            }
            if (N2)
            {
                N2--;
                label[i] = N + 1;
            }
        }
    }
    for (int i = 0; i < N; i++)
        if (label[i] == N)
            cout << (i + 1) << ' ';
    cout << '\n';
    for (int i = 0; i < N; i++)
        if (label[i] == N + 1)
            cout << (i + 1) << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
}