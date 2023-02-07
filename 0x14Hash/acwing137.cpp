#include <bits/stdc++.h>
using namespace std;
const int N = 100010, SEED = 99991;
typedef long long ll;

int tot;
int snow[N][6], nxt[N], head[N];

int H(int* a) {
	int sum = 0, mul = 1;
	for(int i = 0; i < 6; i++) {
		sum = (sum + a[i]) % SEED;
		mul = (ll)mul * a[i] % SEED;
	}
	return (sum + mul) % SEED;
}

// 暴力比较两雪花是否相同
bool equal(int* a, int* b) {
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 6; j++) {
			bool eq = 1;
			// 正向滚动比较
			for(int k = 0; k < 6; k++)
				if(a[(i+k)%6] != b[(j+k)%6])
					eq = 0;
			if(eq) return 1;
			eq = 1;
			// 正向a,反向b
			for(int k = 0; k < 6; k++)
				if(a[(i+k)%6] != b[(j-k+6)%6])
					eq = 0;
			if(eq) return 1;
		}
	return 0;
}

// 判断是否存在相同雪花,同时插入新雪花
bool insrt(int* a) {
	int val = H(a);
	// 遍历表头head[val]指向的链表,寻找形状相同的雪花
	for(int i = head[val]; i; i = nxt[i])
		if(equal(snow[i], a))
			return true;
	// 未找到相同雪花,插入新雪花
	++tot;
	memcpy(snow[tot], a, sizeof(int) * 6);
	nxt[tot] = head[val];
	head[val] = tot;
	return 0;
}

int main()
{
	int n; scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		int a[10];
		for(int j = 0; j < 6; j++)
			scanf("%d", &a[j]);
		if(insrt(a)) {
			puts("Twin snowflakes found.");
			return 0;
		}
	}
	puts("No two snowflakes are alike.");
	return 0;
}