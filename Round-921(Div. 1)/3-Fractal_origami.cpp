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
const int N = 2e6 + 7, mod = 999999893;
int qpow(int x, int y = mod - 2)
{
   int res = 1;
   for (; y; x = (ll)x * x % mod, y >>= 1)
      if (y & 1)
         res = (ll)res * x % mod;
   return res;
}
int inv4 = qpow(4);
struct num
{
   int x, y;
   num(int X = 0, int Y = 0)
   {
      x = X, y = Y;
   }
};
num operator+(num a, num b)
{
   return num((a.x + b.x) % mod, (a.y + b.y) % mod);
}
num operator-(num a, num b)
{
   return num((a.x + mod - b.x) % mod, (a.y + mod - b.y) % mod);
}
num operator*(num a, num b)
{
   return num(((ll)a.x * b.x + (ll)2 * a.y * b.y) % mod, ((ll)a.x * b.y + (ll)a.y * b.x) % mod);
}
struct mat
{
   num a, b;
   mat(num A = num(0, 0), num B = num(0, 0))
   {
      a = A, b = B;
   }
} M[32];
mat operator*(mat a, mat b)
{
   return mat(a.a * b.a, a.b * b.a + b.b);
}
int n;
void Main()
{
   cin >> n;
   num cur = num(0, 0);
   R(i, 30, 0)
   if ((n - 1) >> i & 1) cur = cur * M[i].a + M[i].b;
   cur = (cur + num(4, 0)) * num(inv4, 0);
   cout << (ll)cur.y *
               qpow(((ll)cur.x * cur.x % mod + mod - (ll)2 * cur.y % mod * cur.y % mod) % mod) % mod
        << '\n';
}
int main()
{
   ios ::sync_with_stdio(false);
   cin.tie(0);
   cout.tie(0);
   M[0] = mat(num(0, 1), num(0, 2));
   L(i, 1, 30)
   {
      M[i] = M[i - 1] * M[i - 1];
   }
   int t;
   cin >> t;
   while (t--)
      Main();
   return 0;
}