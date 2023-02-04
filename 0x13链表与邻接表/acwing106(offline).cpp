#include <bits/stdc++.h>
using namespace std;
const int N = 100010;

struct Node {
	int a, w, prv, nxt;
	bool operator < (const Node x) const {
		return a < x.a;
	}
} a[N];

int b[N], ans[N];

void remove(int p) {
	a[a[p].nxt].prv = a[p].prv;
	a[a[p].prv].nxt = a[p].nxt;
}

void solve(int n) {
	int cnt = 0;
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i++) {
		// b[i]为第i个加入数在有序链表中次序
		b[a[i].w] = i;
		a[i].prv = i - 1;
		a[i].nxt = i + 1;
	}
	int mid = n + 1 >> 1;
	ans[++cnt] = a[mid].a; // 先将最后的中位数存储

	// 按加入顺序的反顺序每次取两个点删除
	for(int i = n; i > 1; i -= 2) {
		// 选出目前对应数字在有序序列的位置p1,p2
		int p1 = b[i], p2 = b[i - 1];
		if(p1 > p2) swap(p1, p2);

		// 已满足p1<p2,当前删除数在中位右时,向左移动中位指针
		if(p1 >= mid) mid = a[mid].prv;
		else if(p2 <= mid) mid = a[mid].nxt;

		ans[++cnt] = a[mid].a;
		remove(p1);
		remove(p2);
	}
	int t = 0;
	while (cnt--) {
		t++;
		printf("%d ", ans[cnt + 1]);
		if(t % 10 == 0) puts("");
	}
	if(t % 10) puts("");
}

int main()
{
	int p; scanf("%d", &p);
	while (p--) {
		int id, n; scanf("%d%d", &id, &n);
		printf("%d %d\n", id, n + 1 >> 1);

		for(int i = 1; i <= n; i++) {
			int x; scanf("%d", &a[i].a);
			a[i].w = i;
		}
		solve(n);
	}
	return 0;
}