#include <bits/stdc++.h>
#include <string>
using namespace std;

bool isVowel (char ch) {
    return ch == 'a' || ch == 'e';
}

void solve() {
    
    int n;
    string str;
    cin >> n >> str;
    
    string ans = "";
    
    for (int i = n - 1; i >= 0; i--) {
        if (isVowel(str[i]) && !isVowel(str[i - 1])) {
            ans += str[i];
            ans += str[i - 1];
            ans += '.';
            i--;
        } else {
            ans += str[i];
        }
    }
    
    ans.pop_back();
    
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    
}

int32_t main() {
    
    int t = 1;
    cin >> t;
    
    for(int tc = 1; tc <= t; tc++) {
        solve ();
    }
    
    return 0;
}