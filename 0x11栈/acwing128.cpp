#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;

int n;
stack<int> a, b;
int sum[N], mx[N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	mx[0] = -1e4; // 求最大值,需初始化为极小值
	cin >> n;
	while (n--) {
		char op; cin >> op; // scanf会将\n读入
		if(op == 'I') {
			int x; cin >> x;
			a.push(x);
			sum[a.size()] = sum[a.size()-1] + a.top();
			mx[a.size()] = max(mx[a.size()-1], sum[a.size()]);
		}
		if(op == 'D')
			if(!a.empty())
				a.pop();
		if(op == 'L')
			if(!a.empty()) {
				b.push(a.top());
				a.pop();
			}
		if(op == 'R')
			if(!b.empty()) {
				a.push(b.top());
				b.pop();
				sum[a.size()] = sum[a.size()-1] + a.top();
				mx[a.size()] = max(mx[a.size()-1], sum[a.size()]);
			}
		if(op == 'Q') {
			int x; cin >> x;
			cout << mx[x] << endl;
		}
	}
	return 0;
}