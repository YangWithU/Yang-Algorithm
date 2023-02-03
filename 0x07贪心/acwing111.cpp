#include <bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= int(n); ++i)
using namespace std;
const int N = 200010;
typedef pair<int, int> PII;

int n;
int idx[N];
pair<PII, int> cows[N];

int main()
{
	scanf("%d", &n);
	rep(i, n) {
		scanf("%d%d", &cows[i].first.first, &cows[i].first.second);
		cows[i].second = i;
	}

	sort(cows + 1, cows + n + 1);

	priority_queue<PII, vector<PII>, greater<PII>> heap;
	rep(i, n) {
		if(heap.empty() || heap.top().first >= cows[i].first.first) {
			PII cur = make_pair(cows[i].first.second, heap.size());
			idx[cows[i].second] = cur.second;
			heap.push(cur);
		} else {
		auto cur = heap.top();
			heap.pop();
			cur.first = cows[i].first.second;
			idx[cows[i].second] = cur.second;
			heap.push(cur);
		}
	}
	printf("%d\n", heap.size());
	rep(i, n) printf("%d\n", idx[i] + 1);
	return 0;
}