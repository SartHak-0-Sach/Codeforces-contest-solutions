#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
using LL = long long;

int main()
{

   cin.tie(0);
   cout.tie(0);
   ios::sync_with_stdio(0);

   int T;
   cin >> T;
   while (T--)
   {
      int n;
      cin >> n;
      vector<int> a(n + 1), d(n + 1);
      for (int i = 1; i <= n; i++)
         cin >> a[i];
      for (int i = 1; i <= n; i++)
         cin >> d[i];
      vector<int> l(n + 1), r(n + 1);
      for (int i = 1; i <= n; i++)
      {
         l[i] = i - 1;
         r[i] = i + 1;
      }
      r[n] = 0;

      set<pair<int, int>> s;

      auto get = [&](int x)
      {
         return d[x] - a[l[x]] - a[r[x]];
      };

      vector<bool> v(n + 1);

      auto del = [&](int x)
      {
         if (l[x] && !v[l[x]])
            s.erase({get(l[x]), l[x]});
         if (r[x] && !v[r[x]])
            s.erase({get(r[x]), r[x]});
         r[l[x]] = r[x];
         l[r[x]] = l[x];
         if (l[x] && !v[l[x]])
            s.insert({get(l[x]), l[x]});
         if (r[x] && !v[r[x]])
            s.insert({get(r[x]), r[x]});
      };

      for (int i = 1; i <= n; i++)
      {
         s.insert({get(i), i});
      }

      vector<int> ans(n + 1);
      for (int i = 1; i <= n; i++)
      {
         vector<int> cand;
         while (!s.empty() && s.begin()->first < 0)
         {
            cand.push_back(s.begin()->second);
            v[cand.back()] = true;
            s.erase(s.begin());
         }
         if (cand.empty())
            break;
         ans[i] = cand.size();
         for (auto x : cand)
         {
            del(x);
         }
      }

      for (int i = 1; i <= n; i++)
      {
         cout << ans[i] << " \n"[i == n];
      }
   }
}