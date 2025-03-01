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

const int  N=20010;
char ansr[N][4] = {0};
char str[N];
int main()
{  
    int n, f;
    scanf("%d %d", &n, &f);
    scanf("%s", str);
    int ans = 0;
    for (char i = 'a'; i <= 'z'; i++) {
        for (char j = 'a'; j <= 'z'; j++) {
            if (i != j) {  //0 1 2
                char m[4] = { i,j,j,'\0'};
                bool fl[N] = { 0 };
                int cut=0;

                for (int q = 0; q < n; q++) {
                    if (str[q] == m[0] && str[q + 1] == m[1] && str[q + 2] == m[2])
                    {
                        cut++; 
                        fl[q] = 1;
                        fl[q+1] = 1;
                        fl[q+2] = 1;
                        q += 2;
                    }
                }
                for (int q = 0; q < n; q++) {
                    if (fl[q ]||fl[q + 1]||fl[q +2])continue;
                    if ((str[q + 1] == m[1] && str[q + 2] == m[2])
                        || (str[q] == m[0] && str[q + 1] == m[1])
                        || (str[q] == m[0] && str[q + 2] == m[2]))
                    {
                         cut++;
                         break;
                    }
                }
                if (cut >= f) {
                    ansr[ans][0] = m[0];
                    ansr[ans][1] = m[1];
                    ansr[ans][2] = m[2];
                    ansr[ans][3] = m[3];
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans);
    for (int i = 0; i < ans; i++) {
        printf("%s\n", ansr[i]);
    }
}
