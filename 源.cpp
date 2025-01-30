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

long long int f[12][1<<12];
int n, m;
int cheak(int a) {
	int fig = 0;
	for (int i = 0; i < m; i++) {
		if (a & 1) {
			if (fig & 1)return 0;
			fig = 0;
		}else fig++;
		a >>= 1;
	}
	if (fig & 1)return 0;
	return 1;
}

int main() {
	

	while(cin>>n>>m,n||m)
	{
		if(n==0)
			cout << 0 << endl;
		else if (n == 1) {
			cout << !(m &1 ) << endl;
		}
		else {
			for (int i = 0; i < (1 << m); i++)
				f[1][i]= cheak(i);

			for (int i = 2; i < n; i++) {
				for (int q = 0; q < (1 << m); q++) {
					for (int w = 0; w < (1 << m); w++) {
						if (!(q & w) && f[1][q | w]) {
							f[i][q] += f[i - 1][w];
						}
					}
				}
			}
			long long int ans = 0;
			for (int w = 0; w < (1 << m); w++)
				if(w&& f[1][w])
					ans += f[n - 1][w];
			cout << ans << endl;
		}
	}
}
