#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

void solve(){
   vector<int> v;
   int l=0, r=1e18;
   int n; cin >> n;
   for (int i=1; i<=n; ++i){
      int o, x; cin >> o >> x;
      if (o==1) l=max(l, x);
      else if (o==2) r=min(r, x);
      else v.push_back(x);
   }
   sort(all(v)); v.resize(unique(all(v))-v.begin());
   if (l>r) cout << 0;
   else cout << (r-l+1)-(upper_bound(all(v), r)-lower_bound(all(v), l));
   cout << '\n';
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
