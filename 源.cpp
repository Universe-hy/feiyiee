#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>

using namespace std;

bool is_prime(int x)
{
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0)
            return false;
    return true;
}

int main()
{
    int n;
    cin >> n;

    while (n--)
    {
        int x;
        cin >> x;
        if (is_prime(x)) puts("Yes");
        else puts("No");
    }

    return 0;
}