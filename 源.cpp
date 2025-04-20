#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1000300;
int a[N];
ll s[N];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 1; i < n; i++)
    {
        s[i] = s[i - 1] + (ll)a[i] * a[i] - (ll)a[i - 1] * a[i - 1];
    }
    ll ans = (ll)(1e15);
    for (int i = 0, q = m - 1; q < n; i++, q++)
    {
        ans = min(ans, s[q] - s[i]);
    }
    cout << ans;
    return 0;
}