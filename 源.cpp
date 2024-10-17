#include<iostream>
#include<cstring>
#include<queue>
#include<stack>
#include<map>

using namespace std;

string s;
queue<int> a;
queue<char> b;
map<char, int> m = { {'+',1},{'-',1},{'*',2},{'/',2} };

int count() {
	int	n = a.front();
	int f = b.front();
	a.pop();
	b.pop();
	while (a.size())
	{
		if (!b.size() || m[f] >= m[b.front()]) {
			if (f == '+') n += a.front();
			else if (f == '-')n -= a.front();
			else if (f == '*')n *= a.front();
			else n /= a.front();
		}
		else
		{
			a.push(n);
			b.push(f);
			n = a.front();
		}
		a.pop();
		if (b.size())
		{
			f = b.front();
			b.pop();
		}
	}
	return n;
}

int main() {

	while(1)
	{
		cin >> s;
		for (int i = 0; s[i]; i++) {
			if (s[i] < '9' && s[i]>'0')
				a.push(s[i] - '0');
			else
				b.push(s[i]);
		}

		a.front() = 1;

		cout << count() << endl;
	}
	return 0;
}

