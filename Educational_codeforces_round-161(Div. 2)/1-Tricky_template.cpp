#include <iostream>
#include <queue>
using namespace std;
int n, t;
char a[22], b[22], c[22];
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%s%s%s", &n, a, b, c);
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != c[i] && b[i] != c[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("YES\n");
        else
            printf("No\n");
    }
    return 0;
}