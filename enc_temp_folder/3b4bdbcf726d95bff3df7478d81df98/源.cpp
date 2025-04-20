#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include <queue>
#include<stack>
using namespace std;
const int N = 110;

typedef pair<int, int> PII;

typedef long long ll;
int ma[10][10];

int cheak(int p) {
	int a[5], m = p;
	for (int i = 0; i < 4; i++) {
		a[i] = (m & 0b1111);
		m >>= 4;
	}

	int x[4] = { 0 }, y[4] = { 0 };
	int mk[4][4] = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int q = 0; q < 4; q++) {
			if ((mk[i][q] = (a[i] & (1 << q)/1))) {
				x[i]++;
				y[q]++;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int q = 0; q < 4; q++) {
			if (ma[i][q] ^ ((x[i] + y[q] - mk[i][q]) & 1))
				return 0;
		}
	}

	int num = 0;
		m=p;
	while (m) {
		num += (m & 1);
		m >>= 1;
	}

	for (int i = 0; i < 4; i++) {
		for (int q = 0; q < 4; q++) {
			if ((x[i] + y[q]) & 1)
			{
				printf("%d %d\n", i, q);
			}
		}
	}
	return 1;
}

int main()
{
	string s;
	for (int i = 0; i < 4; i++) {
		cin >> s;
		for (int q = 0; q < 4; q++) {
			ma[i][q] = (s[q] == '+');
		}
	}

	for (int i = 45067; i < (1<<16); i++)
	{
		if (cheak(i))
			break;
	}
	return 0;
}




