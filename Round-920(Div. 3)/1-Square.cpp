#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        vector<pair<int, int>> xAxis(4);
        for (int i = 0; i < 4; i++)
        {
            cin >> xAxis[i].first;
            cin >> xAxis[i].second;
        }
        std::sort(xAxis.begin(), xAxis.end());
        cout << (xAxis[1].second - xAxis[0].second) * (xAxis[2].first - xAxis[1].first) << endl;
    }
    return 0;
}

// #include <bits/stdc++.h>

// #define itn int
// #define all(x) (x).begin(), (x).end()
// #define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())

// using namespace std;

// inline int nxt() {
// 	int x;
// 	cin >> x;
// 	return x;
// }

// void solve() {
// 	int mn = 1e9, mx = -1e9;
// 	for (int i = 0; i < 4; ++i) {
// 		int x = nxt();
// 		mn = min(mn, x);
// 		mx = max(mx, x);
// 		nxt();
// 	}
// 	cout << (mx - mn) * (mx - mn) << "\n";
// }

// int main() {
// 	ios_base::sync_with_stdio(false);
// 	cin.tie(nullptr);

// 	int t = nxt();
// 	while (t--) {
// 		solve();
// 	}

// 	return 0;
// }