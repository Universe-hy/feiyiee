#define _CRT_SECURE_NO_WARNINGS 1
#define struct_size 10
#define queue_size 5
#pragma warning(disable:6031)

#include <windows.h>
#include<iostream>
#include<string>
#include<map>
using namespace std;

//%  &   '  ��  �� *   +   ,   -   .  /
//37 38  39  40 41 42  43  44  45  46 47        
//4  5   6   7  8   9  10  0   1   2  3      ��ɢ�� ģ11
//2  0   0   0  0   2  1   0   1   0  2      ���ȼ�
int pr[11] = { 0,1,0,2,2,0,0,0,0,2,1 };

string buffer;

struct Mystack 
{
    int* top = NULL;
    int* base = (int*)malloc(struct_size * sizeof(int));
    int size = 0;
    int maxSize= struct_size;
}num,op;

struct Myqueue {
    string date[5];
    int res[5] = {0};
    int front=0;
    int rear=0;
    int maxSize = 5;
}oldstr;

void push(struct Myqueue& a,string date,int res) {
    if ((a.rear - a.front +1)%a.maxSize) {
        a.date[a.rear] = date;
        a.res[a.rear] = res;
        a.rear = (a.rear + 1) % a.maxSize;
    }
    else {
        a.date[a.rear] = date;
        a.res[a.rear] = res;
        a.rear  = (a.rear + 1)%a.maxSize;
        a.front = (a.front + 1) % a.maxSize;
    }
}

int pop(struct Mystack &a) {
    if (!a.size)  return 0;
    a.top = --a.size ? a.top -1 : NULL;
    return 1;
}

int push(struct Mystack &a, int b) {
    if (a.size >= a.maxSize) {
        if(realloc(a.base,(a.maxSize + 10) * sizeof(int))){
            printf("׷�ӿռ�ʧ�ܣ������ż򻯻�ֶ�������ʽ\n");
            return 0;
        }
        a.top = a.base + a.maxSize;
        a.maxSize += 10;
    }
    a.size? ++a.top:a.top = a.base;
    *a.top = b; a.size++;
    return 1;
}
//ִ��ջ������
int mathe() {
    if (num.top == NULL)return 0;
    int a = *num.top; pop(num);
    if (num.top == NULL ||op.top==NULL)return 0;
    if (*op.top == '+') {
        *num.top += a;
    }
    else if (*op.top == '-') {
        *num.top -= a;
    }
    else if (*op.top == '*') {
        *num.top *= a;
    }
    else if (*op.top == '/') {
        if(a) *num.top /= a;
        else {
            printf("�����������  ");
            return 0;
        }
    }
    else if (*op.top == '%') {
        if(a) *num.top %= a;
        else {
            printf("����ȡģ������  ");
            return 0;
        }
    }
    pop(op);
    return 1;
}

int jisuan() {
    int n = 0; int count = 0;
    while (buffer[n])
    {
        if (isdigit(buffer[n])) {
            count *= 10;
            count += buffer[n] - '0';
        }else {

            if (count && !push(num, count))return 0;
            count = 0;

            if (buffer[n] == ')' && op.size) {
                while (*op.top != '(') if (!mathe())return 0;
                pop(op);
            }else {
                if (buffer[n] != '(')
                while (op.size && *op.top != '(' &&
                    pr[buffer[n] %11] <= pr[*op.top % 11]) {
                    if (!mathe())return 0;
                }
                if (!push(op, buffer[n]))return 0;  
            }
        }
        n++;
    }

    if (count && !push(num, count))return 0;
    while (op.size)if (!mathe())return 0;   
    return 1;
}
char aa[3] = "��";
//�����ʽ 
int check() {
   
    if(buffer[0]=='0'&& !buffer[1])exit(0);
    for (int i = 0; buffer[i]; i++)
        if ((buffer[i] < '0' || '9' < buffer[i])
            && buffer[i] != '('
            && buffer[i] != ')'
            && buffer[i] != '+'
            && buffer[i] != '-'
            && buffer[i] != '*'
            && buffer[i] != '/'
            && buffer[i] != '%') {
            if (buffer[i] == aa[0] && buffer[i + 1] == aa[1])
                buffer[i] = ')';
            else
                return 0;
        }
            
    return 1;
}
//Ŀ¼
void menu() {
    system("cls");
    printf("|-----------------------------------------------------------|\n");
    printf("|                 ��ӭʹ���������ʽ��������                |\n");
    printf("|-----------------------------------------------------------|\n");
    printf("|                                                           |\n");
    printf("|֧�ֵĲ����У��ӣ�+��������-�����ˣ�*��������/����ȡģ��%c��|\n",'%');
    printf("|                               (����0���س��˳�����)       |\n");
    printf("|___________________________________________________________|\n\n");
    for (int i = oldstr.front; i != oldstr.rear; i = (i + 1)%oldstr.maxSize) {
        cout << oldstr.date[i] << " = ";
        cout << oldstr.res[i] << endl;
    }
    printf("�����������������ʽ ��\n");
}

int main() {   
    menu();
    while (1) {
        cin >> buffer;
        menu();
        cout << buffer <<" =" << endl;
        if (check() && jisuan() && num.top != NULL) {
            printf("%d\n", *num.top);
            push(oldstr,buffer, *num.top);
        }
        else {
            printf("ע�⣺��������ȷ�ı��ʽ����\n");
        }
        while(num.size) pop(num);
        while (op.size)pop(op);
    }
    return 0;
}
