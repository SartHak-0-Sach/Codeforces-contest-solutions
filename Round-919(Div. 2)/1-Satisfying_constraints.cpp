#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    
    int n, m;
    cin >> n >> m;
    
    vector<pair<int,int>> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    vector<vector<int>> dist(n, vector<int>(n, 1e17));
    vector<vector<int>> vis(n, vector<int>(n, 0));
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    
    dist[0][0] = 0;
    pq.push({0, 0, 0});
    
    while (!pq.empty()) {
        int city = pq.top()[1];
        int bike = pq.top()[2];
        pq.pop();
        
        if (city == n - 1) {
            cout << dist[city][bike] << endl;
            return;
        }
        
        if (vis[city][bike]) continue;
        vis[city][bike] = 1;
        
        
        for (auto it : adj[city]) {
            int nbr = it.first;
            int wt = it.second;
            
            int newBike = bike;
            if (s[nbr] < s[bike]) newBike = nbr;
            
            if (dist[nbr][newBike] < dist[city][bike] + wt * s[bike]) continue;
            
            dist[nbr][newBike] = dist[city][bike] + wt * s[bike];
            pq.push({dist[nbr][newBike], nbr, newBike});
        }
    }
    
    cout << -1 << endl;
}

int32_t main() {
    
    int t = 1;
    cin >> t;
    
    for(int tc = 1; tc <= t; tc++) {
        solve ();
    }
    
    return 0;
}