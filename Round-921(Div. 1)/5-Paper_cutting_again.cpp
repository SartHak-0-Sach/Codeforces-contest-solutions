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
const int N = 2e6 + 7, mod = 1e9 + 7;
int qpow(int x, int y = mod - 2)
{
   int res = 1;
   for (; y; x = (ll)x * x % mod, y >>= 1)
      if (y & 1)
         res = (ll)res * x % mod;
   return res;
}
int fac[N], ifac[N], inv[N];
void init(int x)
{
   fac[0] = ifac[0] = inv[1] = 1;
   L(i, 2, x)
   inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
   L(i, 1, x)
   fac[i] = (ll)fac[i - 1] * i % mod,
   ifac[i] = (ll)ifac[i - 1] * inv[i] % mod;
}
int C(int x, int y)
{
   return x < y || y < 0 ? 0 : (ll)fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
inline int sgn(int x)
{
   return (x & 1) ? mod - 1 : 1;
}

ll n, m, k;
void Main()
{
   cin >> n >> m >> k;
   if ((ll)n * m < k)
   {
      cout << 0 << '\n';
      return;
   }
   int ans = 1;
   L(sum, 2, n + m - 2)
   {
      int cnt = 0;
      ll l = max(1LL, sum - n + 1), r = min(m - 1, sum - 1LL);
      ll mid = sum / 2;
      if (mid * (sum - mid) >= k)
      {
         --l, ++r;
         R(t, 19, 0)
         {
            ll nl = l + (1 << t);
            if (nl <= mid && nl * (sum - nl) < k)
               l = nl;
         }
         R(t, 19, 0)
         {
            ll nr = r - (1 << t);
            if (nr >= mid && nr * (sum - nr) < k)
               r = nr;
         }
         ++l, --r;
         if (l <= r)
            cnt = r - l + 1;
      }
      (ans += (ll)inv[sum] * inv[sum - 1] % mod * 2 % mod * cnt % mod) %= mod;
   }
   // L(i, 1, m - 1) {
   // 	L(j, 1, n - 1) {
   // 		int buf = (ll)inv[i + j] * inv[i + j - 1] % mod * 2 % mod;
   // 		if((ll)i * j >= k) (ans += buf) %= mod;
   // 	}
   // }

   L(i, 1, m - 1)
   if ((ll)n * i >= k)(ans += inv[n + i - 1]) %= mod;
   L(i, 1, n - 1)
   if ((ll)m * i >= k)(ans += inv[m + i - 1]) %= mod;
   cout << ans << '\n';
}
int main()
{
   ios ::sync_with_stdio(false);
   cin.tie(0);
   cout.tie(0);
   init(2e6);
   int t;
   cin >> t;
   while (t--)
      Main();
   return 0;
}