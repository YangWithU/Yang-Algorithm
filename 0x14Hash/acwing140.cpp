#include <bits/stdc++.h>
using namespace std;
const int N = 300010, SEED = 131;
typedef unsigned long long ull;

ull f[N], p[N];
int n;
int sa[N], height[N];
char s[N];

ull getHash(int a, int b) {
	return f[b] - f[a - 1] * p[b - a + 1];
}

// 传入两个下标,返回最长公共前缀的长度
int lcp(int x, int y) {
	int l = 0, r = min(n - x + 1, n - y + 1);
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if(getHash(x, x + mid - 1) == getHash(y, y + mid - 1)) l = mid;
		else r = mid - 1;
	}
	return l;
}

// sort中比较函数,两个序列跳过公共长度后
// 将字典序小的放前面
bool cmp(int x, int y) {
	int len = lcp(x, y);
	return s[x + len] < s[y + len];
}

// 计算height
// 直接求当前和上一个前缀最长公共序列长度即可
void calcHeight() {
	for(int i = 2; i <= n; i++)
		height[i] = lcp(sa[i - 1], sa[i]);
}

int main()
{
	scanf("%s", s + 1);
	n = strlen(s + 1);
	p[0] = 1;
	for(int i = 1; i <= n; i++) {
		sa[i] = i;
		f[i] = f[i - 1] * SEED + (s[i] - 'a' + 1);
		p[i] = p[i - 1] * SEED;
	}
	sort(sa + 1, sa + n + 1, cmp);
	calcHeight();
	for(int i = 1; i <= n; i++) printf("%d ", sa[i] - 1); puts("");
	for(int i = 1; i <= n; i++) printf("%d ", height[i]);
	return 0;
}