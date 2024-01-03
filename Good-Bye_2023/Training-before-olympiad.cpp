#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void final(vector<int> a, int b, int c)
{
    vector<int> temp = a;
}

int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);

        if (n == 1)
        {
            cout << a[0] << endl;
        }

        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        vector<int> ans;
        ans[0] = a[0];
        ans[1] = floor((a[0] + a[1]) / 2) * 2;

        for(int i = 2; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                
            }
            
        }
    }
    return 0;
}
