#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include <stdlib.h>
#include<string>
#include<map>
using namespace std;

int ve[22][22],f[1048580][22];

int main() {
	int n,a;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int q = 0; q < n; q++)
			cin >> ve[i][q];
	//q 为取数状态
	for (int q = 3; q < (1 << n); q += 2)
	{
		//以i 为结尾
		for (int i = 0; i < n; i++) {
			f[q][i] = 1000;
			if (i && (q & (1 << i)))
			{
				//j 为上一个结尾
				for (int j = 0; j < n; j++)
				{
					if ((q & (1 << j)) && j != i)
						f[q][i] = min(f[q][i], f[q ^ (1 << i)][j] + ve[j][i]);
				}
			}
		}
	}

	cout << f[(1 << n ) - 1][n - 1];
}
