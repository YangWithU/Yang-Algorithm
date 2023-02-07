#include <bits/stdc++.h>
using namespace std;
const int N = 1000010, SEED = 131;

char s[N];
// f 表示前缀字串s[1~i]的hash值
// p 表示当前SEED的i次方,方便后面计算
unsigned long long f[N], p[N];

int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	p[0] = 1;
	for(int i = 1; i <= n; i++) {
		f[i] = f[i - 1] * SEED + (s[i] - 'a' + 1);
		p[i] = p[i - 1] * SEED;
	}	
	int q; scanf("%d", &q);
	for(int i = 1; i <= q; i++) {
		int l1, l2, r1, r2;	
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		// 通过比较hash值进行字符串是否相同的比较
		if(f[r1] - f[l1 - 1] * p[r1 - l1 + 1] == 
			f[r2] - f[l2 - 1] * p[r2 - l2 + 1])
			puts("Yes");
		else puts("No");
	}
	return 0;
}