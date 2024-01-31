#include<bits/stdc++.h>

using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define isz(x) ((int)x.size())
#define sumof(x) accumulate(all(x), 0ll)

const int dx[]={1, -1, 0, 0}, dy[]={0, 0, 1, -1};
int n, m, Q;

void solve(){
   cin >> n >> m >> Q;
   vector<vector<char>> a(n+1, vector<char>(m+1));
   int ix=-1, iy=-1;
   vector<vector<int>> dist(n+1, vector<int>(m+1, -1));
   queue<pair<int, int>> q;
   for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j){
      cin >> a[i][j];
      if (a[i][j]=='#') ix=i, iy=j;
      if (a[i][j]=='v'){
         q.emplace(i, j);
         dist[i][j]=0;
      }
   }
   while (q.size()){
      int x=q.front().first, y=q.front().second;
      q.pop();
      for (int k=0; k<4; ++k){
         int u=x+dx[k], v=y+dy[k];
         if (u<1 || v<1 || u>n || v>m || dist[u][v]!=-1) continue;
         dist[u][v]=dist[x][y]+1;
         q.emplace(u, v);
      }
   }
   while (Q--){
      int xs, ys; cin >> xs >> ys;
      int l=0, r=dist[xs][ys];
      while (l<=r){
         int mid=(l+r)>>1;
         queue<pair<pair<int, int>, int>> qq;
         vector<vector<vector<int>>> f(n+1, vector<vector<int>>(m+1, vector<int>(2, 0)));
         qq.push({{xs, ys}, 0});
         f[xs][ys][0]=1;
         while (qq.size()){
            int x=qq.front().first.first, y=qq.front().first.second, z=qq.front().second;
            qq.pop();
            for (int k=0; k<4; ++k){
               int u=x+dx[k], v=y+dy[k], z2=z;
               if (u<1 || v<1 || u>n || v>m || dist[u][v]<mid || a[u][v]=='#') continue;
               if (y<=iy && iy<v && ix<=x) z2^=1;
               else if (v<=iy && iy<y && ix<=x) z2^=1;
               if (f[u][v][z2]) continue;
               f[u][v][z2]=1;
               qq.push({{u, v}, z2});
            }
         }
         if (f[xs][ys][1]) l=mid+1;
         else r=mid-1;
      }
      cout << r << '\n';
   }
}

int32_t main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   int ntests=1;
   // cin >> ntests;
   for (int i=1; i<=ntests; ++i) solve();
   return 0;
}
