#include <bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= int(n); ++i)
using namespace std;
const int N = 1800010, SZ = log2(N);

int n, q;
int a[N], mx[N][SZ], mn[N][SZ];

void st_pre() {
	int k = log2(n);
	for(int j = 1; j <= k; j++)
		for(int i = 1; i <= n - (1 << j) + 1; i++) {
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
			mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
		}
}

int st_query(int l, int r) {
	int k = log2(r - l + 1);
	return max(mx[l][k], mx[r - (1 << k) + 1][k]) - min(mn[l][k], mn[r - (1 << k) + 1][k]);
}

int main()
{
	scanf("%d%d", &n, &q);
	rep(i, n) {	/* Initialise: 从区间i,长度0开始 */
		int x;
		scanf("%d", &x);
		mx[i][0] = x, mn[i][0] = x;
	}
	st_pre();
	
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		int ans = st_query(l, r);
		printf("%d\n", ans);
	}
	return 0;
}