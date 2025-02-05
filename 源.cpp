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
const int N = 10010;
int a[N];

int main()
{
    int n;
    cin >> n;
    int b;
    for (int i = 0; i < n; i++) {
        cin >> b;
        a[b]++;
    }
    int ans =0,sum=0;
    for (int i = 1; i < 10010; i++) {
        for (int q = 0; q < a[i]; q++) {
            sum += i;
            ans += sum;
        }
    }
    cout << ans;
    return 0;
}
