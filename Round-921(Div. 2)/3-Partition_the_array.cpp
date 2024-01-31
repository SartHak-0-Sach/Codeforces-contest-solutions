#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

const int N=2e5+10;
int n;
int a[N];

void solve(){
   cin >> n;
   for (int i=1; i<=n; ++i) cin >> a[i];
   int ans=0;
   for (int k=1; k<=n; ++k) if (n%k==0){
      vector<vector<int>> v(k);
      for (int i=1; i<=n; ++i) v[i%k].push_back(a[i]);
      int d=0;
      for (auto &i:v){
         if (isz(i)==1) continue;
         for (int j=1; j<isz(i); ++j) d=__gcd(d, abs(i[j]-i[j-1]));
      }
      ans+=(d!=1);
   }
   cout << ans << '\n';
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
