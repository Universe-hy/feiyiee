#include<iostream>
#include<algorithm>
#include <stdlib.h>
using namespace std;
typedef long long int ll;

const int  N = 400010;
int w5 = (1 << 5) - 1;
int cheak(ll i) {
	int a = 0, b = w5;

	int ka = 0, kb = 1, ya = 0, yb = 1;

	for (int q = 0; q < 25; q += 5) {

		int k = (i >> q) & w5;
		if (k == 0 || k == w5)
			return 0;
		a |= k;
		b &= k;

		int x = (k >> (4 - q / 5)) & 1;
		ka |= x;
		kb &= x;

		int y = (k >> (q / 5)) & 1;
		ya |= y;
		yb &= y;
	}
	if (a != w5 || b != 0)
		return 0;
	if (ka != 1 || kb != 0)
		return 0;
	if (ya != 1 || yb != 0)
		return 0;

	int num = 0;
	while(i) {
		num += i & 1;
		i >>= 1;
	}
	if (num != 13)
		return 0;
	return 1;
}
int main() {
	ll ans = 0;
	for (ll i = 0; i < (1 << 25); i++) {
		ans += cheak(i);
	}
	cout << ans;
	return 0;
}