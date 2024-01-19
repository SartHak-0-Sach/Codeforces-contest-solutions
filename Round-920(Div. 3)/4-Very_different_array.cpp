#include <bits/stdc++.h>

#define itn int
#define all(x) (x).begin(), (x).end()
#define make_unique(x) \
	sort(all((x)));    \
	(x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt()
{
	int x;
	cin >> x;
	return x;
}

void solve()
{
	int n = nxt(), m = nxt();
	vector<long long> a(n);
	vector<long long> b(m);
	generate(all(a), nxt);
	generate(all(b), nxt);
	auto f = [&](auto &v)
	{
		sort(all(v));
		v.insert(v.begin(), 0);
		for (int i = 1; i < (int)v.size(); ++i)
		{
			v[i] += v[i - 1];
		}
	};
	f(a);
	f(b);
	long long ans = 0;
	for (int i = 0; i <= n; ++i)
	{
		ans = max(ans, b[m] - b[m - i] - a[i] + a[0] + a[n] - a[i] - b[n - i] + b[0]);
	}
	cout << ans << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t = nxt();
	while (t--)
	{
		solve();
	}

	return 0;
}