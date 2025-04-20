#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

string s[2];
int main()
{
    cin >> s[0] >> s[1];

    int be = 0, ed = 0;
    for (int i = 0; s[0][i]; i++)
        if (s[0][i] == '#' || s[1][i] == '#')
        {
            be = i;
            break;
        }
    for (int i = 0; s[0][i]; i++)
        if (s[0][i] == '#' || s[1][i] == '#')
            ed = i;

    int f0 = (s[0][be] == '#');
    int f1 = (s[1][be] == '#');
    int f2 = 0;
    int ans = 0;


    for (int i = be + 1; i <= ed; i++)
    {
        int k0 = (s[0][i] == '#'), k1 = (s[1][i] == '#');
        if ((f0 && k0) || (f1 && k1) || (f2 && (k0 || k1)))
        {
            f0 = k0;
            f1 = k1;
            f2 = 0;
        }
        else
        {
            ans++;
            if (f0 == f1)
            {
                f0 = k0;
                f1 = k1;
                f2 = 1;
            }
            else
            {
                f0 = f0 || k0;
                f1 = f1 || k1;
                f2 = 0;
            }
        }
    }
    cout << ans;

}


