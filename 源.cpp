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

int a[90];
int dp[90][90];
int re[80] = { 1 };
struct LongInt
{
    ll a[80];
    ll M = 100;
    bool operator<(const LongInt& t) const
    {
        if (a[0] != t.a[0])
            return a[0] < t.a[0];
        for (int i = a[0]; i > 0; i--) {
            if (a[i] != t.a[i])
                return a[i] < t.a[i];
        }
        return 0;
    }

    LongInt operator+(const LongInt& t) const
    {
        struct LongInt ans;
        ans.a[0] = max(a[0], t.a[0]);
        ll ji=0;
        
        for (int i = 1; i <= ans.a[0] ; i++) {
            ans.a[i] = a[i] + t.a[i]+ji;
            ji = ans.a[i] / M;
            ans.a[i] %= M;
        }
        if (ji) {
            ans.a[0]++;
            ans.a[ans.a[0]] = ji;
        }
        return ans;
    }

    /*LongInt operator+=(const LongInt& t) const
    {
        a[0] = max(a[0], t.a[0]);
        ll ji = 0;

        for (int i = 1; i <= a[0]; i++) {
            a[i] = a[i] + t.a[i] + ji;
            ji = a[i] / M;
            a[i] %= M;
        }
        if (ji) {
            a[0]++;
            a[a[0]] = ji;
        }
    }*/
}lin[2];
int main()
{
    struct LongInt k,t ;
    k.a[0] = 2;

    k.a[1] = 94;
    k.a[2] = 94;
    //k.a[3] = 98;

    t.a[0] = 2;
    t.a[1] = 98;
    t.a[2] = 98;
    //t.a[3] = 98;
    k = k + t;
    int ak=0;

    

    /*int n, m;
    scanf("%d %d", &n, &m);
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        re[i] = re[i - 1] * 2;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 1; i <= m; i++)
            scanf("%d", &a[i]);

        for (int i = 1; i <= m; i++) {
            for (int q = 1; q <= i+1; q++) {
                dp[i][q] = max(dp[i - 1][q - 1] + a[q - 1] * re[i], dp[i - 1][q] + a[q+m-i]*re[i]);
            }
        }
        int count = 0;
        for (int i = 0; i <= m; i++) {
            count = max(count,dp[m][i]);
        }
        ans += count;
    }
    printf("%d", ans);*/
}
