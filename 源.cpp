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

const int  N=1000010;
ll a[N],n;
int ai[N];
int num[N];
bool fa[N], f[N];
int main()
{  
    scanf("%lld", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        num[i] = num[i - 1];
        if (!f[a[i]])
        {
            f[a[i]] = 1;
            num[i]++;
        }
    } 
    ll ans = 0;
    for (int i = n; i > 0; i--) {
        ai[a[i]]++;
        if (ai[a[i]] == 2 && !fa[a[i]]) {
            fa[a[i]] = 1;
            if (num[i] == num[i - 1])
                ans += num[i - 1] - 1;
            else
                ans += num[i - 1];
        }
    }
    printf("%lld", ans);
}
