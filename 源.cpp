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
const int N = 100010;
char a[N];

int wei(int x) {
    int ans = 0;
    while (x) {
        x /= 10;
        ans++;
    }
    return x;
}

int ten[10];
int main()
{
    ten[0] = 1;
    for (int i = 1; i < 10; i++) {
        ten[i] = ten[i - 1] * 10;
    }
    int n,m;
    cin >> n;
    int num = 0;
    cin >> a;
    int res = 0,r=0;
    int k = 0;
    for(int i=0;i<n;i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        int er = wei(r);
        for (int e = wei(l); e <=er ; e++) {
            if(e>=3)
                for (int q = 1; q < 10; q++)
                {
                    int rw = e;
                    int qw = rw / 2;
                    int kw = rw - 2;
                    for (int k = 0; k < ten[kw]; k++) {
                        int ka = k / ten[kw / 2];
                        int kb = k % ten[kw / 2];
                        res = q * ten[qw * 2] + ka * ten[qw + 1] + q * ten[qw] + kb * ten[1] + q;
                        if (res < r)
                            printf("%d ", res);
                    }
                }
            else {
                for (int k = 0; k < 10; k++) {
                    if (l <= k && k <= r)
                        printf("%d ", k);
                }
            }
        }
    }

    return 0;
}

