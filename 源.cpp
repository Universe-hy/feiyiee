#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include<string>
#include<map>
#include<queue>
using namespace std;
typedef long long int ll;

const int  N = 100010;
int ans[105][1<<20];
int ansma[105][1 << 20];
int ma[205];
int n, m;
int cheak(int x, int y) {
    int q1 = x >> m;
    int q2 = x - (q1 << m);
    int q3 = y >> m;
    int q4 = y - (q3 << m);
    return ((q4 & (q3 | q2)) | (q3 & (q1 | q2))) ? 0 : 1; //((q3 & q2 & q1 | (q4 & q3 & q2)));
}

int cheak(int q) {
    return (q & ((q >> 1) | (q >> 2)));
}


void print(int i,int w) {
    if (i < 0)return;
    print(i - 1, ansma[i][w]);
    for (int q = m*2-1; q >=0; q--) {
        if ((w >> q) & 1) {
            cout << '*';
        }
        else {
            if ((ma[i] >> q) & 1) {
                cout << 'H';
            }
            else {
                cout << 'P';
            }
        }
        if (q % m ==0)
            cout << endl;
    }
}
int main() {
    cin >> n >> m;

    //ma ≥ı ºªØ
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        for (int q = 0; q < m; q++) {
            ma[i/2] <<= 1;
            ma[i/2] += (str[q] == 'H');
        }
    }
    if (n & 1)
        ma[n / 2] = (ma[n / 2] << m) + (1 << m) - 1;
    ma[n / 2 + 1] = (1 << (2 * m)) - 1;


    for (int i = 0; i < (n + 1)/2; i++) {
        for (int q = 0; q < (1 << (m * 2)); q++) {
            int q1 = q >> m, q2 = q - (q1 << m);
            //ºÏ—Èq 
            if ((q1 & q2) | cheak(q1) | cheak(q2) | (q & ma[i]))
                continue;
            if(i)
            {
                int maxn = 0;
                for (int w = 0; w < (1 << (m * 2)); w++) {
                    if (cheak(w, q)) {
                        if (maxn<ans[i - 1][w])
                        {
                            maxn = ans[i - 1][w];
                            ansma[i][q] = w;
                        }
                    }
                }
                ans[i][q] += maxn;
            }
            for (int w = q; w; w >>= 1) {
                ans[i][q] += (w & 1);
            }
        }
    }
    int ans1 = 0;
    int anma = 0;
    for (int i = 0; i < (1 << (m * 2)); i++) {
        if (ans1 < ans[(n + 1) / 2 - 1][i])
        {
            ans1 = ans[(n + 1) / 2 - 1][i];
            anma = i;
        }
    }
    cout << ans1<<endl;
    print((n + 1) / 2 - 1,anma);
    return 0;
}

