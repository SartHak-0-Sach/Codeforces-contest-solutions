#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

const int N=1e5+1, inf=2e18;
int n, q, cnt[N];
pair<int, int> a[N];
pair<int, vector<int>> b[N];

void solve(){
   cin >> n >> q;
   int m=0, sz=0;
   for (int i=1; i<=n; ++i){
      cin >> a[i].first >> a[i].second;
      if (m && b[m].first==1 && a[i].first==1) b[m].second.push_back(a[i].second);
      else b[++m]={a[i].first, {a[i].second}};
   }
   for (int i=1; i<=m; ++i){
      if (b[i].first==1){
         sz=min(sz+isz(b[i].second), inf);
      }else{
         if (sz>=inf/(b[i].second[0]+1)) sz=inf;
         else sz*=(b[i].second[0]+1);
      }
      cnt[i]=sz;
   }
   int m2=m;
   while (cnt[m-1]==inf) --m;
   for (int i=1; i<=q; ++i){
      int idx; cin >> idx;
      int ans=-1;
      for (int j=m; j>=1; --j){
         if (b[j].first==1){
            if (cnt[j]-idx+1<=isz(b[j].second)){
               ans=b[j].second[idx-(cnt[j]-isz(b[j].second))-1];
               break;
            }
         }else{
            int prev_sz=cnt[j-1];
            idx=(idx-1)%prev_sz+1;
         }
      }
      cout << ans << ' ';
   }
   cout << '\n';
   for (int i=1; i<=m2; ++i) b[i]={0, {}};
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
