#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 100010;
int a[n];

int main()
{
	int n, k;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> k;
		a[k]++;
	}
	for (int i = 100000; i > 0; i--)
	{
		int num = 0;
		for (ll q = i; q <= 100000; q *= i)
		{
			num += a[q];
		}
		if (num >= 3)
		{
			for (ll q = i; q <= 100000; q *= i)
			{
				if (a[q]) {
					printf("%d ", q);
				}
			}
			break;
		}
	}
	return 0;
}