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

struct LongInt
{
    ll a[101] = {0};
    ll M = 1000000000;
    int K = 9;//注意put中缩进的修改
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
        struct LongInt ans = { 0 };
        ans.a[0] = max(a[0], t.a[0]);
            
        for (int i = 1; i <= ans.a[0] ; i++) {
            if(i<=a[0])
                ans.a[i]+= a[i];
            if (i <= t.a[0])
                ans.a[i] += t.a[i];
            ans.a[i+1] += ans.a[i] / M;
            ans.a[i] %= M;
        }
        if (ans.a[ans.a[0]+1]) {
            ans.a[0]++;
        }
        return ans;
    }

    LongInt operator*(const LongInt& t) const
    {
        struct LongInt ans = { 0 };
        ans.a[0] = a[0] + t.a[0] -!(a[a[0]]*t.a[t.a[0]]/M);
        
        for (int i = 1; i <= a[0]; i++) {
            for (int j = 1; j <= t.a[0]; j++) {
                ans.a[i + j -1] += a[i] * t.a[j];
                ans.a[i + j] += ans.a[i + j - 1] / M;
                ans.a[i + j - 1] %= M;
            }
        }
        return ans;
    }
    // 45 134 643 723 563 4  //23 273
    void stingInit(string str) {
        a[0] = str.size() / K + (str.size() % K ? 1 : 0);
        for (int i = 1; i<= a[0]; i++) {
            ll num = 0;
            for (int q = 0; q < K; q++) {
                num *= 10;
                if ((int)str.size() - i * K + q >= 0)
                    num += str[str.size() - i * K + q] - '0';
            }
            a[i] = num;
        }
    }

    void put() {
        printf("%lld", a[a[0]]);
        for (int i = a[0]-1; i > 0; i--)
            printf("%09lld", a[i]);
    }
};
struct LongInt a[82];
struct LongInt dp[82][82];
struct LongInt r[82] = { 1,1 };
int main()
{  
    int n, m;
    scanf("%d %d", &n, &m);
    struct LongInt ans = {0};
    struct LongInt re = {0};
    re.a[0] = 1;
    re.a[1] = 2;
    for (int i = 1; i <= m; i++) {
        r[i] = r[i - 1] * re;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 1; i <= m; i++)
        {
            a[i].a[0] = 1;
            scanf("%lld", &a[i].a[1]);
        }

        for (int i = 1; i <= m; i++) {
            for (int q = 1; q <= i+1; q++) {
                dp[i][q] = {0};
                struct LongInt re1 = a[q - 1] * r[i] + dp[i - 1][q - 1];
                struct LongInt re2 = a[q + m - i] * r[i] + dp[i - 1][q];
                if (re1 < re2)
                    dp[i][q] = re2;
                else
                    dp[i][q] = re1;
            }
        }
        struct LongInt count = {0};
        for (int i = 0; i <= m; i++) {
            if(count<dp[m][i])
                count = dp[m][i];
        }
        ans = ans + count;
    }
    ans.put();
}
