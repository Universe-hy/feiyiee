#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
typedef long long int ll;

const int  N = 400010;

int a[N], idx;
int main() {
    int T, num = 0, min_num = 1e9;
    char c;
    cin >> T;
    getchar();

    int r_num = 0;
    while (T-- && (c = getchar()) == '1') {
        r_num++;
    }
    while (T--) {
        c = getchar();
        if (c == '1') {
            num++;
        }
        else if (num) {
            a[idx++] = num;
            min_num = min(num, min_num);
            num = 0;
        }
    }
    int l_num = num;

    int m = (min_num - 1) / 2 * 2 + 1;
    if (r_num) {
        m = min(m, r_num * 2 - 1);
        a[idx++] = r_num;
    }
    if (l_num) {
        m = min(m, l_num * 2 - 1);
        a[idx++] = l_num;
    }
    int ans = 0;

    for (int i = 0; i <= idx; i++) {
        ans += a[i] / m + (a[i] % m ? 1 : 0);
    }
    cout << ans;

    return 0;
}