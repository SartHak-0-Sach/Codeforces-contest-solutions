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
	int n = nxt();
	string s, t;
	cin >> s >> t;
	int c[2] = {0, 0};
	for (int i = 0; i < n; ++i)
	{
		if (s[i] != t[i])
		{
			c[s[i] - '0'] += 1;
		}
	}
	cout << max(c[0], c[1]) << "\n";
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