#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 100010;
const ll M = (ll)1000000007;
int a[N];

ll xpow(int a, int b)
{
	ll ans = 1;
	while (b) {
		if (b & 1)ans = ans * a % M;
		a = (ll)a * a % M;
		b >>= 1;
	}
	return (ans * 2) % M;
}

int main()
{
	ll n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}

	int e = 0;
	ll ans = 0;
	for (int i = 1; i < n; i++)
	{
		e ^= a[i];
		ans += (ll)e * xpow(3, n - i - 1) % M;
	}
	ans += e ^ a[n];
	cout << ans % M;
	return 0;
}