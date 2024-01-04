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

namespace atcoder
{

    namespace internal
    {

        // @param n `0 <= n`
        // @return minimum non-negative `x` s.t. `n <= 2**x`
        int ceil_pow2(int n)
        {
            int x = 0;
            while ((1U << x) < (unsigned int)(n))
                x++;
            return x;
        }

        // @param n `1 <= n`
        // @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
        constexpr int bsf_constexpr(unsigned int n)
        {
            int x = 0;
            while (!(n & (1 << x)))
                x++;
            return x;
        }

        // @param n `1 <= n`
        // @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
        int bsf(unsigned int n)
        {
#ifdef _MSC_VER
            unsigned long index;
            _BitScanForward(&index, n);
            return index;
#else
            return __builtin_ctz(n);
#endif
        }

    } // namespace internal

} // namespace atcoder

namespace atcoder
{

    template <class S,
              S (*op)(S, S),
              S (*e)(),
              class F,
              S (*mapping)(F, S),
              F (*composition)(F, F),
              F (*id)()>
    struct lazy_segtree
    {
    public:
        lazy_segtree() : lazy_segtree(0) {}
        explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
        explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size()))
        {
            log = internal::ceil_pow2(_n);
            size = 1 << log;
            d = std::vector<S>(2 * size, e());
            lz = std::vector<F>(size, id());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--)
            {
                update(i);
            }
        }

        void set(int p, S x)
        {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = x;
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }

        S get(int p)
        {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            return d[p];
        }

        S prod(int l, int r)
        {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return e();

            l += size;
            r += size;

            for (int i = log; i >= 1; i--)
            {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            S sml = e(), smr = e();
            while (l < r)
            {
                if (l & 1)
                    sml = op(sml, d[l++]);
                if (r & 1)
                    smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }

            return op(sml, smr);
        }

        S all_prod() { return d[1]; }

        void apply(int p, F f)
        {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = mapping(f, d[p]);
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }
        void apply(int l, int r, F f)
        {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return;

            l += size;
            r += size;

            for (int i = log; i >= 1; i--)
            {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            {
                int l2 = l, r2 = r;
                while (l < r)
                {
                    if (l & 1)
                        all_apply(l++, f);
                    if (r & 1)
                        all_apply(--r, f);
                    l >>= 1;
                    r >>= 1;
                }
                l = l2;
                r = r2;
            }

            for (int i = 1; i <= log; i++)
            {
                if (((l >> i) << i) != l)
                    update(l >> i);
                if (((r >> i) << i) != r)
                    update((r - 1) >> i);
            }
        }

        template <bool (*g)(S)>
        int max_right(int l)
        {
            return max_right(l, [](S x)
                             { return g(x); });
        }
        template <class G>
        int max_right(int l, G g)
        {
            assert(0 <= l && l <= _n);
            assert(g(e()));
            if (l == _n)
                return _n;
            l += size;
            for (int i = log; i >= 1; i--)
                push(l >> i);
            S sm = e();
            do
            {
                while (l % 2 == 0)
                    l >>= 1;
                if (!g(op(sm, d[l])))
                {
                    while (l < size)
                    {
                        push(l);
                        l = (2 * l);
                        if (g(op(sm, d[l])))
                        {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template <bool (*g)(S)>
        int min_left(int r)
        {
            return min_left(r, [](S x)
                            { return g(x); });
        }
        template <class G>
        int min_left(int r, G g)
        {
            assert(0 <= r && r <= _n);
            assert(g(e()));
            if (r == 0)
                return 0;
            r += size;
            for (int i = log; i >= 1; i--)
                push((r - 1) >> i);
            S sm = e();
            do
            {
                r--;
                while (r > 1 && (r % 2))
                    r >>= 1;
                if (!g(op(d[r], sm)))
                {
                    while (r < size)
                    {
                        push(r);
                        r = (2 * r + 1);
                        if (g(op(d[r], sm)))
                        {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;
        std::vector<F> lz;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
        void all_apply(int k, F f)
        {
            d[k] = mapping(f, d[k]);
            if (k < size)
                lz[k] = composition(f, lz[k]);
        }
        void push(int k)
        {
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            lz[k] = id();
        }
    };

} // namespace atcoder

using ll = int64_t;
using S = ll;
using F = S;
S op(S x, S y) { return max(x, y); }
S e() { return -1e9; }
S mapping(F f, S x) { return f + x; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

void solve()
{
    int N;
    cin >> N;
    vector<int> par(N);
    vector<vector<int>> ch(N);
    for (int i = 1; i < N; i++)
    {
        cin >> par[i];
        par[i]--;
        ch[par[i]].push_back(i);
    }
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
        a[i]--;
    }
    vector<int> st(N), en(N);
    vector<int> idx(N);
    int t = 0;
    y_combinator(
        [&](auto self, int v) -> void
        {
            st[v] = t;
            idx[t] = v;
            t++;
            for (int w : ch[v])
                self(w);
            en[v] = t;
        })(0);
    ll ans = 0;

    vector<set<int>> active_locs(N);
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<ll>(N, 0));
    y_combinator(
        [&](auto self, int v) -> void
        {
            for (int w : ch[v])
            {
                self(w);
            }
            while (true)
            {
                auto z = active_locs[a[v]].lower_bound(st[v]);
                if (z != active_locs[a[v]].end() && *z < en[v])
                {
                    int loc = idx[*z];
                    active_locs[a[v]].erase(z);
                    seg.apply(st[loc], en[loc], -1);
                }
                else
                    break;
            }
            seg.apply(st[v], en[v], 1);
            active_locs[a[v]].insert(st[v]);
            ll m1 = 1;
            ll m2 = 1;
            for (int w : ch[v])
            {
                m2 = max(m2, seg.prod(st[w], en[w]));
                if (m2 > m1)
                    swap(m1, m2);
            }
            ans = max(ans, m1 * m2);
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