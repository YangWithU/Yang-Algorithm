#include <bits/stdc++.h>
using namespace std;
const int N = 1010;

int n, root;

struct Node {
	int father, size, sum;
	double avg;
} nodes[N];

int fnd_max() {
	double avg = 0;
	int res = -1;
	for(int i = 1; i <= n; ++i) {
		if(i != root && avg < nodes[i].avg) {
			avg = nodes[i].avg;
			res = i;
		}
	}
	return res;
}

int main()
{
	int ans = 0;
	scanf("%d%d", &n, &root);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &nodes[i].sum);
		nodes[i].size = 1;
		nodes[i].avg = nodes[i].sum;
		ans += nodes[i].sum;
	}
	for(int i = 0; i < n - 1; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		nodes[b].father = a;
	}

	for(int i = 0; i < n - 1; ++i) {
		int cur = fnd_max();
		int ftr = nodes[cur].father;
		ans += nodes[cur].sum * nodes[ftr].size;
		nodes[cur].avg = -1;
		// 已然合并，将被合并点父节点修改至当前点
		for(int j = 1; j <= n; ++j)
			if(nodes[j].father == cur)
				nodes[j].father = ftr;
		// 合并子节点总和，节点数，avg到父节点
		nodes[ftr].sum += nodes[cur].sum;
		nodes[ftr].size += nodes[cur].size;
		nodes[ftr].avg = (double)nodes[ftr].sum / nodes[ftr].size;
	}
	printf("%d", ans);
	return 0;
}