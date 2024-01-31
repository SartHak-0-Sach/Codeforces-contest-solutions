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
const int N = 3007, mod = 1e9 + 7;
string s;
int n, k, m;
int dp[26];
void Main()
{
   cin >> n >> k >> m;
   cin >> s;
   string cur;
   int pos = 0;
   for (int i = 1; i <= n; ++i)
   {
      me(dp, 0x3f);
      L(j, pos, sz(s) - 1)
      {
         dp[s[j] - 'a'] = min(dp[s[j] - 'a'], j);
      }
      int mx = max_element(dp, dp + k) - dp;
      cur += mx + 'a';
      if (dp[mx] >= sz(s))
      {
         cout << "NO\n";
         while (sz(cur) < n)
            cur += 'a';
         cout << cur << '\n';
         return;
      }
      pos = dp[mx] + 1;
   }
   cout << "YES\n";
}
int main()
{
   ios ::sync_with_stdio(false);
   cin.tie(0);
   cout.tie(0);
   int t;
   cin >> t;
   while (t--)
      Main();
   return 0;
}