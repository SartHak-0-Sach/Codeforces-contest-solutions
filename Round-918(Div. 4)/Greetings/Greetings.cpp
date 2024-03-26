#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using oset = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

void solve() {
    
    int n;
    cin >> n;
    
    vector<vector<int>> a(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    
    sort (a.begin(), a.end());
    
    oset<int> st;
    for (int i = 0; i < n; i++) {
        st.insert (a[i][1]);
    }
    
    long long ans = 0;
    
    for (int i = 0; i < n; i++) {
        ans += st.order_of_key(a[i][1]);
        st.erase(a[i][1]);
    }
    
    cout << ans << endl;
}

int main() {
    
    int t = 1;
    cin >> t;
    
    for(int tc = 1; tc <= t; tc++) {
        solve ();
    }
    
    return 0;
}