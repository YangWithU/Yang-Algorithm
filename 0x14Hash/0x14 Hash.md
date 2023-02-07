# 0x14 Hash

Hash表由Hash函数与链表组成。与离散化类似，是将大量数据映射到可维护值域内进行搜索等方式的过程。映射时发生重合，我们可以采用“开散列”的方式，将小区间用邻接表的head维护。发生重合，则统一接到当前head之下。

Hash基本包含两种操作：

1. 计算Hash函数的值
2. 定位到对应链表中比较，遍历

有必要设计能够分配均匀的Hash函数，使得每次查找所需时间可降为`原始信息总数除以表头数组长度`，即为$O(1)$。

## 数字hash

### [acwing137](https://www.acwing.com/problem/content/description/139/)

本题给我们许多雪花，让我们判断输入中是否存在两个相同的雪花。

运用在线哈希算法，我们可以将输入的每一个雪花抽象成一串数字，之后加入head数组每个元素对应的链表之中。每次加入前先扫描对应链表，如果存在相同，则输出存在相同雪花，否则仅插入链表。

利用哈希函数将雪花的信息抽象成一串数字，将哈希函数设计为雪花`(六个边之和%SEED + 六个边乘积%SEED) % SEED`，其中SEED取题目小于n范围的最大素数，本题中为`99991`。

```c++
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
```

## 字符串hash

取一个固定值`P`，将要处理的字符串看作`P`进制数。同时分配一个大于0的数值代表每个字符 (*比如a = 1, b = 2...z = 26*)。之后，再取一固定值`M`，求`P`进制数对`M`的余数，作为该字符串的hash值`H(str)`

> 一般而言，$P = $`131` 或 $P = $`13331`，$M = 2 ^ {64}$
>
> $M = 2^{64}$，直接用`unsigned long long`存储hash值，溢出时相当于直接对$$2^{64}$$取模

如果想要保证我们所有的数据不出问题，我们可以多次hash，使用不同的`P,M`保证加密后结果相同。

所有对于字符串的操作，都可以直接对P进行算术运算反映到Hash值上。

假设字符串`S`的hash值为`H(S)`，则在`S`的末尾添加一个字符`c`构成的新串:

+ $$ H(S + c) = (H(S) * P + value[c]) \quad mod \quad M $$

> 乘P相当于将原字符串左移P进制下一位，$value[c]$是我们为c选定的代表数值

设`S+T`的hash值为`H(S+T)`，则：

+ $$ H(T) = ( H(S+T) - H(S) * P^{length(T)}) \quad mod \quad M$$

> 相当于通过P进制下，在S后边补充0的方式，将`S`左移到与`S + T`左端对齐，之后二者相减从而得到H(T)

**例如，$S = $`abc`, $c = $`d`, $T = $`xyz`, 则：**

+ $S_{(p)} = $ `1 2 3`，$H(S) = 1 * P^2 + 2 * P + 3$，
+ $H(S + c) = 1 * P^3 + 2 * P^2 + 3 * P + 4 = H(S) * P + 4$
+ $S + T = $ `1 2 3 24 25 26`, $H(S+T) = 1 * P^5 + 2 * P^4 + 3 * P^3 + 24 * P^2 + 25 * P + 26$

### [acwing138](https://www.acwing.com/problem/content/140/) 

给定一个字符串，询问该串任意区间是否相同，相同输出`Yes`否则`No`

```c++
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
```

### [acwing139](https://www.acwing.com/problem/content/141/) 

给定一个字符串，求其最长回文字串长度

```c++
const int N = 1000010, P = 131;
typedef unsigned long long ull;
char s[N];
ull f1[N], f2[N], p[N];

// 正序[a~b]的hash
ull H1(int a, int b) {
	return (f1[b] - f1[a-1] * p[b-a+1]);
}

// 逆序[a~b]的hash
ull H2(int a, int b) {
	return (f2[a] - f2[b+1] * p[b-a+1]);
}

int main()
{
	int id = 0;
	p[0] = 1;
	for(int i = 1; i < N; i++) p[i] = p[i-1] * P; // 预处理 P^i
	while (scanf("%s", s+1) && !(s[1] == 'E' && s[2] == 'N' && s[3] == 'D')) {
		id++;
		int ans = 0, len = strlen(s+1);
		f2[len+1] = 0;
		for(int i = 1; i <= len; i++) f1[i] = f1[i-1] * P + s[i];
		for(int i = len; i; i--) f2[i] = f2[i+1] * P + s[i];
		//遍历一遍整个字符串
		for(int i = 1; i <= len; i++) {
		    //i前字串长度为当前最长回文串一半长度,此情况为奇数串
			int l = 0, r = min(i-1, len-i);
			while (l < r) {
				int mid = (l + r + 1) >> 1; //取i前子串一半为mid，
				//以i为中心，二分改变左右l,r指针的位置，对比左右两串是否相同
				if(H1(i-mid, i-1) == (H2(i + 1, i + mid))) l = mid;
				else r = mid - 1;
			}
			ans = max(l * 2 + 1, ans); //最终的l居字符串中心,直接*2+1即回文串的长度
            // 同样求一遍偶数串时的情况
			l = 0, r = min(i-1, len-i+1);
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				if(H1(i-mid, i-1) == H2(i, i+mid-1)) l = mid;
				else r = mid - 1;
			}
			ans = max(l * 2, ans);
		}
		printf("Case %d: %d\n", id, ans);
	}
	return 0;
}
```

### [acwing140](https://www.acwing.com/problem/content/142/)

我们可以利用hash来比较两个字符串是否相同，同时使用二分来查询出两个字符串的相同长度。以上两部构成查询`最长公共字串`操作，我们可以利用此操作：

+ 跳过字串公共长度将后缀串排序
+ 比较后缀串相同的长度

```c++
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
```
