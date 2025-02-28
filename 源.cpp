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
const int  N=1000;

int a[3][N][N];
int num[N];
int main()
{  
    int n, Q;
    scanf("%d %d", &n, &Q);
    for (int i = 0; i < 3; i++) {
        for (int q = 0; q < n; q++) {
            for (int w = 0; w < n; w++) {
                a[i][q][w] = n;
            }
        }
    }
    int ans = 0;
    for (int q = 0; q < Q; q++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if(!--a[0][y][z])ans++;
        if(!--a[1][x][y])ans++;
        if(!--a[2][x][z])ans++;
        printf("%d\n", ans);
    }
}
