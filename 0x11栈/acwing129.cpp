#include <bits/stdc++.h>
using namespace std;
const int N = 200010;

int n, cnt = 0;
stack<int> stk;
vector<int> path;

void dfs(int u) {
	if(u == n + 1) {
		if(++cnt > 20)
			return;
		for(auto x : path)
			cout << x;
		stack<int> opt(stk);
		while (!opt.empty()) {
			cout << opt.top();
			opt.pop();
		}
		cout << endl;
		return;
	}

	if(!stk.empty()) {
		path.push_back(stk.top());
		stk.pop();
		dfs(u);
		stk.push(path.back());
		path.pop_back();
	}
	
	stk.push(u);
	dfs(u + 1);
	stk.pop();
}

int main()
{
	cin >> n;
	dfs(1);
	return 0;
}