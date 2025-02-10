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
int main()
{
    int n, m = 0; int a;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        if (i & 1)
            m ^= a;
    }
    printf(m ? "Yes" : "No");
    return 0;
}

