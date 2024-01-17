#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

const int N=2510, mod=998244353;
int f[N][N], n, k;

void add(int &x, int y){
   x=x+y>=mod?x+y-mod:x+y;
}

void solve(){
   cin >> n >> k;
   for (int i=0; i<=n; ++i) f[0][i]=1;
   for (int i=1; i<=n; ++i){
      for (int j=0; j<=i; ++j){
         for (int t=0; t<=n; ++t){
            int d=i-(j+1)*(t+1);
            if (d<0 || j+t+1>k) break;
            add(f[i][j], f[d][t]);
         }
      }
   }
   int ans=0;
   for (int i=0; i<=n; ++i) add(ans, f[n][i]);
   cout << ans << '\n';
   for (int i=0; i<=n; ++i) for (int j=0; j<=n; ++j) f[i][j]=0;
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
