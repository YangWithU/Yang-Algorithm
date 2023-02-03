#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1000010, M = 1010;

int t, id = 0;
int f[N];
char s[10];
queue<int> q[M];

void solve() {
	q[0] = queue<int>(); // 清空
	for(int i = 1; i <= t; i++) {
		int n; scanf("%d", &n);
		for(int j = 1; j <= n; j++) {
			int x; scanf("%d", &x);
			f[x] = i;
		}
		q[i] = queue<int>(); // 清空
	}
	printf("Scenario #%d\n", ++id);
	while (scanf("%s", s) && s[0] != 'S') {
		if(s[0] == 'E') {
			int x; scanf("%d", &x);
			if(q[f[x]].empty()) q[0].push(f[x]);
			q[f[x]].push(x);
		} else {
			int x = q[0].front();
			printf("%d\n", q[x].front());
			q[x].pop();
			if(q[x].empty()) q[0].pop();
		}
	}
	puts("");
}

int main()
{
	while (scanf("%d", &t) && t) solve();
	return 0;
}