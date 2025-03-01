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

const int  N=20010;
ll a[N],n;

int main()
{  
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &n);
        ll all = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a[i]);
            a[i] += a[i-1];
        } 
        ll ai = a[n];
        for (int i = 0; i  <= (n - 1) / 2; i++) {
            ai = min(ai, a[n / 2 + 1 + i] - a[i]);
        }
        printf("%lld %lld", ai, a[n] - ai);
    }
}
