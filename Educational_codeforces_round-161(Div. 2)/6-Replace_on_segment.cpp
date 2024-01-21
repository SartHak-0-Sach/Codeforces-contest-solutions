#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
using LL = long long;
const int INF = 1e9;
int dp[105][105][105], a[105];
int mn1[105][105], mn2[105][105];

int main()
{

   cin.tie(0);
   cout.tie(0);
   ios::sync_with_stdio(0);

   int T;
   cin >> T;
   while (T--)
   {
      int n, x;
      cin >> n >> x;
      for (int i = 1; i <= n; i++)
      {
         for (int j = i; j <= n; j++)
         {
            mn1[i][j] = mn2[i][j] = 0;
            for (int k = 0; k <= x; k++)
            {
               dp[i][j][k] = INF;
            }
         }
      }
      for (int i = 1; i <= n; i++)
      {
         cin >> a[i];
         for (int j = 1; j <= x; j++)
         {
            dp[i][i][j] = 1;
         }
         dp[i][i][a[i]] = 0;
         mn1[i][i] = a[i];
         mn2[i][i] = 1 + (a[i] == 1);
      }
      if (x == 1)
      {
         cout << 0 << '\n';
         continue;
      }
      for (int len = 2; len <= n; len++)
      {
         for (int l = 1; l + len - 1 <= n; l++)
         {
            int r = l + len - 1;
            for (int i = 1; i <= x; i++)
            {
               for (int j = l; j < r; j++)
               {
                  dp[l][r][i] = min(dp[l][r][i], dp[l][j][i] + dp[j + 1][r][i]);
               }
            }
            vector<vector<int>> pos(x + 1);
            for (int i = l; i <= r; i++)
            {
               pos[a[i]].push_back(i);
            }
            for (int i = 1; i <= x; i++)
            {
               if (pos[i].empty())
               {
                  dp[l][r][i] = min(dp[l][r][i], 1);
                  continue;
               }
               vector<int> f(pos[i].size() + 1, INF);
               f[0] = 1;
               for (int j = 0; j < pos[i].size(); j++)
               {
                  int R = pos[i][j];
                  for (int k = 0; k <= j; k++)
                  {
                     int L = pos[i][k];
                     int cost = 0;
                     if (mn1[L][R] == i)
                     {
                        cost = dp[L][R][mn2[L][R]];
                     }
                     else
                     {
                        cost = dp[L][R][mn1[L][R]];
                     }
                     f[j + 1] = min(f[j + 1], f[k] + cost);
                  }
               }
               dp[l][r][i] = min(dp[l][r][i], f.back());
            }
            for (int i = 1; i <= x; i++)
            {
               if (dp[l][r][i] <= dp[l][r][mn1[l][r]])
               {
                  mn2[l][r] = mn1[l][r];
                  mn1[l][r] = i;
               }
               else if (dp[l][r][i] < dp[l][r][mn2[l][r]])
               {
                  mn2[l][r] = i;
               }
            }
         }
      }
      int ans = INF;
      for (int i = 1; i <= x; i++)
      {
         ans = min(ans, dp[1][n][i]);
      }
      cout << ans << '\n';
   }
}