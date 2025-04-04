#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
typedef long long int ll;

const int  N = 1000010;

int num[N];
int qnum[N];

int sum[N];

ll n, m;
int main() {
    int T;
    cin >> T;
    while (T--) {
        memset(num, 0 ,sizeof(num));
        memset(qnum, 0, sizeof(qnum));
        memset(sum, 0, sizeof(sum));
        cin >> n >> m;
        int ai,ans=1e9;
        for (int i = 0; i < n; i++) {
            cin >> ai;
            num[ai % m]++;
        }

        //єу m/2ПоєН
        for (int i = 0; i < m / 2; i++) {
            sum[0] += num[i];
        }
        for (int i = 0; i < m-1; i++) {
            sum[i+1] = sum[i] - num[i] + num[(i + m / 2) % m];
        }

        qnum[0] = 0;
        for (int i = 1; i < m; i++) {
            qnum[0] += num[i] * min(i,m-i);
        }

        ans = qnum[0];
        for (int x = 1; x < m; x++) {
            qnum[x] = qnum[x - 1] - sum[x] + sum[((m + 1)/2+x) % m];
            ans = min(qnum[x], ans);
        }
        cout << ans << endl;
    }
    return 0;
}

