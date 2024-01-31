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
int n, m, k;
void Main()
{
   cin >> n >> m >> k;
   if (k > n || k > m)
   {
      cout << 0 << '\n';
      return;
   }
   int tmp = 1 + n + m - 2 * k;
   int len = k;
   // cout << tmp << ' ' << len << endl;
   cout << (ll)C(len * 2 + tmp, len) * inv[len * 2 + tmp] % mod * tmp % mod << '\n';
}
int main()
{
   ios ::sync_with_stdio(false);
   cin.tie(0);
   cout.tie(0);
   init(2e5);
   int t;
   cin >> t;
   while (t--)
      Main();
   return 0;
}