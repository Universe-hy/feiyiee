
#include<iostream>
#include<string>
#include<algorithm>
#include <stdlib.h>
#include <set>
#include <queue>
using namespace std;

typedef long long ll;
const int N = 10001;

struct tree {
    int r, l;
    ll n,cout;
    bool operator <(const tree& v) {
        return n < v.n;
    }
} a[N];

ll ans;

ll count(int x,int d) {
    ans += a[x].n * d;
    if (a[x].r)a[x].cout += count(a[x].r, d + 1);
    if (a[x].l)a[x].cout += count(a[x].l, d + 1);
    return a[x].cout += a[x].n;
}

void count(int x,ll res, ll top) {
    ans = min(ans, res);
    top += a[x].n;
    if (a[x].r) count(a[x].r, res - a[a[x].r].cout + a[a[x].l].cout + top, top + a[a[x].l].cout);
    if (a[x].l) count(a[x].l, res + a[a[x].r].cout - a[a[x].l].cout + top, top + a[a[x].r].cout);
}


signed main()
{
    int T;
    cin >> T;
    for(int i= 1;i<=T;i++) cin >> a[i].n >> a[i].r >> a[i].l;
    count(1, 0);
    count(1,ans, (ll)0);
    cout << ans;
    return 0;
}