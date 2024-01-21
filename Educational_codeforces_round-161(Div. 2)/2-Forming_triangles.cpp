#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
using LL = long long;

int main()
{

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    auto C2 = [&](int x)
    {
        return 1LL * x * (x - 1) / 2;
    };

    auto C3 = [&](int x)
    {
        return 1LL * x * (x - 1) * (x - 2) / 6;
    };

    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            cnt[x] += 1;
        }
        LL ans = 0;
        int s = 0;
        for (int i = 0; i <= n; i++)
        {
            ans += C3(cnt[i]) + C2(cnt[i]) * s;
            s += cnt[i];
        }
        cout << ans << '\n';
    }
}