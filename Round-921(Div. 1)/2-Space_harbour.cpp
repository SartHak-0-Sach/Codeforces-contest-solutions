#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); ++i)
#define R(i, j, k) for (int i = (j); i >= (k); --i)
#define ll long long
#define sz(a) ((int)(a).size())
#define vi vector<int>
#define me(a, x) memset(a, x, sizeof(a))
#define ull unsigned long long
#define ld __float128
#define pb emplace_back
using namespace std;
const int N = 1e6 + 7, mod = 1e9 + 7;
template <int N>
struct fenwt
{
   using F = long long;
   F a[N + 1];
   void add(int x, F w)
   {
      for (; x <= N; x += x & -x)
         a[x] += w;
   }
   F query(int x)
   {
      F ret = 0;
      for (; x; x -= x & -x)
         ret += a[x];
      return ret;
   }
   F get(int l, int r)
   {
      if (l > r)
         return 0;
      return query(r) - query(l - 1);
   }
};
fenwt<N> F;
int m, n, q;
pair<int, int> P[N];
int val[N];
set<int> st;
inline ll query(int pos)
{
   if (!pos)
      return 0;
   auto p = st.lower_bound(pos);
   ll ans = F.query(pos);
   if (*p > pos)
   {
      auto pl = p;
      --pl;
      int l = *pl, r = *p;
      ll tl = r - pos, tr = r - l - 1;
      ans += ((tr * (tr + 1) / 2 - tl * (tl - 1) / 2)) * val[l];
   }
   return ans;
}
void make(int l, int r, ll w)
{
   int len = r - l;
   F.add(r, (ll)w * val[l] * len * (len - 1) / 2);
}
void ins(int x, int v)
{
   val[x] = v;
   auto pr = st.lower_bound(x);
   auto pl = pr;
   --pl;
   make(*pl, *pr, -1);
   st.insert(x);
   make(*pl, x, 1);
   make(x, *pr, 1);
}
int main()
{
   ios ::sync_with_stdio(false);
   cin.tie(0);
   cout.tie(0);
   cin >> n >> m >> q;
   L(i, 1, m)
   {
      cin >> P[i].first;
   }
   L(i, 1, m)
   {
      cin >> P[i].second;
      val[P[i].first] = P[i].second;
   }
   sort(P + 1, P + m + 1);
   L(i, 1, m)
   {
      st.insert(P[i].first);
   }
   L(i, 2, m)
   {
      make(P[i - 1].first, P[i].first, 1);
   }
   while (q--)
   {
      int t;
      cin >> t;
      if (t == 1)
      {
         int x, v;
         cin >> x >> v;
         ins(x, v);
      }
      else if (t == 2)
      {
         int l, r;
         cin >> l >> r;
         cout << query(r) - query(l - 1) << '\n';
      }
   }
   return 0;
}