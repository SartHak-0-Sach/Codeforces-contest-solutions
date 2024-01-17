




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
// 	int n = nxt();
// 	int f = nxt(), a = nxt(), b = nxt();
// 	vector<int> ts(n);
// 	generate(all(ts), nxt);
// 	int last = 0;
// 	for (int t : ts) {
// 		long long mn = 1ll * (t - last) * a;
// 		if (b < mn) {
// 			mn = b;
// 		}
// 		if (mn >= f) {
// 			cout << "No\n";
// 			return;
// 		}
// 		f -= mn;
// 		last = t;
// 	}
// 	cout << "Yes\n";
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