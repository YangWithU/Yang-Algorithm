#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;

char s[N];
int nxt[N], n, m;

// 自我匹配找重复前缀
void calcNext() {
	nxt[1] = 0;
	for(int i = 2, j = 0; i <= n; i++) {
		while (j && s[i] != s[j + 1]) j = nxt[j];
		if(s[i] == s[j + 1]) j++;
		nxt[i] = j;
	}
}

int main()
{
	int id = 0;
	while (scanf("%d", &n) && n) {
		scanf("%s", s + 1);
		calcNext();
		printf("Test case #%d\n", ++id);
		// k值计算:当前长度除剩余长度
		for(int i = 2; i <= n; i++) {
			if(i % (i - nxt[i]) == 0 && i / (i - nxt[i]) > 1)
				printf("%d %d\n", i, i / (i - nxt[i]));
		}
		puts("");
	}
	return 0;
}