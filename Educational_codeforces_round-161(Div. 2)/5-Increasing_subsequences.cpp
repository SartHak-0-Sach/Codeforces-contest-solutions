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

    int T;
    cin >> T;
    while (T--)
    {
        LL n;
        cin >> n;
        int t = __lg(n);
        vector<int> ans;
        for (int i = 0; i < t; i++)
        {
            ans.push_back(i);
        }
        for (int i = t - 1; i >= 0; i--)
        {
            if (n >> i & 1)
            {
                ans.push_back(i);
            }
        }
        cout << ans.size() << '\n';
        for (auto x : ans)
            cout << x << ' ';
        cout << '\n';
    }
}