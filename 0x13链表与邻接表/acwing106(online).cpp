#include <bits/stdc++.h>
using namespace std;

int main()
{
	int p;
	scanf("%d", &p);
	while (p--) {
		int id, n; scanf("%d%d", &id, &n);
		printf("%d %d\n", id, n + 1 >> 1);

		priority_queue<int> hq;
		priority_queue<int, vector<int>, greater<int>> sq;

		int cnt = 0;
		for(int i = 0; i < n; i++) {
			int x; scanf("%d", &x);

			if(hq.empty() || x <= hq.top()) hq.push(x);
			else sq.push(x);

			if(hq.size() > sq.size() + 1) sq.push(hq.top()), hq.pop();
			if(sq.size() > hq.size()) hq.push(sq.top()), sq.pop();

			if(i % 2 == 0) {
				printf("%d ", hq.top());
				if(++cnt % 10 == 0) puts("");
			}
		}
		puts("");
	}
	return 0;
}