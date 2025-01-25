#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
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
	// f[(1 << i) | (1 << q)][q];
	for (int i = 1; i <  1<<(n+1)-1; i++)
	{

		for (int q = 0; q < n; q++) {
			if()
			f[q][i] = 1000000000;
			for (int j = 1; j < n; j++)
			{
				if (q & (1 << j))
					f[q][i] = min(f[q][i], f[q][j] + ve[j][i]);
			}
		}
	}
			
}
