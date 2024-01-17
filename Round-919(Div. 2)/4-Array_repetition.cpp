#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        char a[3][3];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cin >> a[i][j];
            }
        }
        int total = 261;
        char missing = 'a';
        int sum = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                sum += static_cast<int>(a[i][j]);
            }
            if (total - sum == 63)
            {
                sum = 0;
                continue;
            }
            else
            {
                missing = static_cast<char>(total - sum);
                cout << missing << endl;
                break;
            }
        }
    }
    return 0;
}