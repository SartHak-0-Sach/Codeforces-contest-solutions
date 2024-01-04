#include <bits/stdc++.h>
using namespace std;

namespace std
{

    template <class Fun>
    class y_combinator_result
    {
        Fun fun_;

    public:
        template <class T>
        explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

        template <class... Args>
        decltype(auto) operator()(Args &&...args)
        {
            return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

    template <class Fun>
    decltype(auto) y_combinator(Fun &&fun)
    {
        return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }

} // namespace std

#include <ext/pb_ds/assoc_container.hpp>

struct splitmix64_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

using ll = int64_t;
void solve()
{
    int N;
    cin >> N;
    vector<vector<pair<int, ll>>> adj(N);
    ll ans = 0;
    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        ans = max(ans, w);
    }
    vector<int> exists(N, 1);
    vector<int> sz(N);
    auto find_centroid = [&](int st) -> int
    {
        y_combinator(
            [&](auto self, int v, int p) -> void
            {
                sz[v] = 1;
                for (auto [w, c] : adj[v])
                {
                    if (w == p || !exists[w])
                        continue;
                    self(w, v);
                    sz[v] += sz[w];
                }
            })(st, -1);
        int total_sz = sz[st];
        int centroid = -1;
        y_combinator(
            [&](auto self, int v, int p) -> void
            {
                if (sz[v] * 2 >= total_sz)
                    centroid = v;
                for (auto [w, c] : adj[v])
                {
                    if (w == p || !exists[w])
                        continue;
                    self(w, v);
                }
            })(st, -1);
        return centroid;
    };

    y_combinator(
        [&](auto self, int st) -> void
        {
            st = find_centroid(st);
            for (int it = 0; it < 2; it++)
            {
                vector<vector<int>> group;
                hash_map<ll, int> paths;
                for (auto [w1, c1] : adj[st])
                {
                    if (!exists[w1])
                        continue;

                    hash_map<ll, int> sub_paths;
                    y_combinator(
                        [&](auto self2, int v, int p, int d, ll g) -> void
                        {
                            sub_paths[g] = max(sub_paths[g], d);
                            ans = max(ans, g * d);
                            for (auto [w, c] : adj[v])
                            {
                                if (w == p || !exists[w])
                                    continue;
                                self2(w, v, d + 1, gcd(g, c));
                            }
                        })(w1, st, 1, c1);
                    for (auto [g, l] : sub_paths)
                    {
                        if (g * l * 2 <= ans)
                            continue;
                        for (ll mult = 1; mult <= l + 1; mult++)
                        {
                            auto z = paths.find(mult * g);
                            if (z != paths.end())
                            {
                                ans = max(ans, g * (l + z->second));
                            }
                        }
                    }
                    for (auto [g, f] : sub_paths)
                    {
                        paths[g] = max(paths[g], f);
                    }
                }
                reverse(adj[st].begin(), adj[st].end());
            }
            exists[st] = 0;
            for (auto [w, c] : adj[st])
            {
                if (!exists[w])
                    continue;
                self(w);
            }
        })(0);
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
        solve();
}