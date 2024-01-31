#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

const int N=2e5+10;
int n, k, x;
int a[N], pf[N];

void solve(){
   cin >> n >> k >> x;
   for (int i=1; i<=n; ++i) cin >> a[i];
   sort(a+1, a+n+1);
   partial_sum(a, a+n+1, pf);
   int ans=-1e18;
   for (int i=n-k; i<=n; ++i){
      int j=max(0ll, i-x);
      ans=max(ans, -(pf[i]-pf[j])+pf[j]);
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
