#include <bits/stdc++.h>
using namespace std;

void solve() {
    
    int n;
    cin >> n;
    
    vector<int> a (n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i & 1) a[i] *= -1;
    }
    
    long long sum = 0;
    set<long long> st {0};
    
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (st.find(sum) != st.end()) {
            cout << "YES" << endl;
            return;
        }
        st.insert (sum);
    }
    
    cout << "NO" << endl;
}

int main() {
    int t = 1;
    cin >> t;
    
    for(int tc = 1; tc <= t; tc++) {
        solve();
    }

    return 0;
}