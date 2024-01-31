#include <bits/stdc++.h>

using namespace std;
int n;
int val[100005];
vector<int> fontos;
bool kerd(int l, int r)
{
   cout.flush() << "? " << l << " " << r << endl;
   int x;
   cin >> x;
   bool jo = (x == r - l + 1);
   for (auto x : fontos)
   {
      if (abs(val[x]) == 3)
         continue;
      if (jo != (l <= x && x <= r))
      {
         val[x] = max(1, val[x] + 1);
      }
      else
      {
         val[x] = min(-1, val[x] - 1);
      }
   }
   /*cout << "ertekek:\n";
   for (auto x:fontos) {
       cout << x << " " << val[x] << "\n";
   }*/
}
void res(int x)
{
   cout << "! " << x << endl;
   char c;
   cin >> c;
}

vector<int> split52(vector<int> sz)
{
   for (auto x : sz)
   {
      val[x] = 0;
   }
   fontos = sz;
   int n = sz.size();
   int a = 0, b = n / 4, c = 2 * n / 4, d = 3 * n / 4, ut = sz.back();
   kerd(sz[a], sz[c] - 1);
   kerd(sz[b], sz[d] - 1);
   kerd(sz[0], ut);

   if (abs(val[sz[a]]) == 2)
   {
      kerd(sz[a], sz[b] - 1);
      if (abs(val[sz[b]]) == 2)
      {
         kerd(sz[b], sz[c] - 1);
      }
      else if (abs(val[sz[c]]) == 2)
      {
         kerd(sz[c], sz[d] - 1);
      }
      else
      {
         kerd(sz[d], ut);
      }
   }

   else if (abs(val[sz[b]]) == 2)
   {
      kerd(sz[b], sz[c] - 1);
      if (abs(val[sz[a]]) == 2)
      {
         kerd(sz[a], sz[b] - 1);
      }
      else if (abs(val[sz[c]]) == 2)
      {
         kerd(sz[c], sz[d] - 1);
      }
      else
      {
         kerd(sz[d], ut);
      }
   }

   else if (abs(val[sz[c]]) == 2)
   {
      kerd(sz[c], sz[d] - 1);
      if (abs(val[sz[a]]) == 2)
      {
         kerd(sz[a], sz[b] - 1);
      }
      else if (abs(val[sz[b]]) == 2)
      {
         kerd(sz[b], sz[c] - 1);
      }
      else
      {
         kerd(sz[d], ut);
      }
   }

   else if (abs(val[sz[d]]) == 2)
   {
      kerd(sz[d], ut);
      if (abs(val[sz[a]]) == 2)
      {
         kerd(sz[a], sz[b] - 1);
      }
      else if (abs(val[sz[b]]) == 2)
      {
         kerd(sz[b], sz[c] - 1);
      }
      else
      {
         kerd(sz[c], sz[d] - 1);
      }
   }

   sz.clear();
   for (auto x : fontos)
   {
      if (abs(val[x]) < 3)
      {
         sz.push_back(x);
      }
   }

   return sz;
}

vector<int> solve3(vector<int> sz)
{
   int a = sz[0], b = sz[1], c = sz[2];
   for (auto x : sz)
   {
      val[x] = 0;
   }
   fontos = sz;
   kerd(a, a), kerd(a, c);

   if (abs(val[a]) == 2)
   {
      kerd(a, a);
      kerd(b, b);
   }
   else if (abs(val[b]) == 2)
   {
      kerd(b, b);
      kerd(c, c);
   }
   else
   {
      kerd(c, c);
      kerd(a, a);
   }

   sz.clear();
   for (auto x : fontos)
   {
      if (abs(val[x]) < 3)
      {
         sz.push_back(x);
      }
   }

   return sz;
}

void solve()
{
   cin >> n;
   vector<int> sz;
   for (int i = 1; i <= n; i++)
   {
      sz.push_back(i);
   }
   while (sz.size() > 3)
   {
      sz = split52(sz);
   }
   if (sz.size() == 3)
   {
      sz = solve3(sz);
   }

   assert(sz.size() <= 2);
   for (auto x : sz)
   {
      res(x);
   }
   cout.flush() << "#" << endl;
}
int main()
{
   ios_base::sync_with_stdio(false);
   int w;
   cin >> w;
   while (w--)
   {
      solve();
   }
   return 0;
}
