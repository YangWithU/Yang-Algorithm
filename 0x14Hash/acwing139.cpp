#include <bits/stdc++.h>
using namespace std;
const int N = 1000010, SEED = 131;
typedef unsigned long long ull;

char s[N];
ull f1[N], f2[N], p[N];

// 正序[a~b]的hash
ull H1(int a, int b) {
	return (f1[b] - f1[a - 1] * p[b - a + 1]);
}

// 逆序[a~b]的hash
ull H2(int a, int b) {
	return (f2[a] - f2[b + 1] * p[b - a + 1]);
}

int main()
{
	int id = 0;
	p[0] = 1;
	for(int i = 1; i < N; i++) p[i] = p[i - 1] * SEED;
	while (scanf("%s", s + 1) && !(s[1] == 'E' && s[2] == 'N' && s[3] == 'D')) {
		id++;
		int ans = 0, len = strlen(s + 1);
		f2[len + 1] = 0;
		for(int i = 1; i <= len; i++) f1[i] = f1[i - 1] * SEED + s[i];
		for(int i = len; i; i--) f2[i] = f2[i + 1] * SEED + s[i];

		for(int i = 1; i <= len; i++) {
			int l = 0, r = min(i - 1, len - i);
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				if(H1(i - mid, i - 1) == H2(i + 1, i + mid)) l = mid;
				else r = mid - 1;
			}
			ans = max(l * 2 + 1, ans);

			l = 0, r = min(i - 1, len - i + 1);
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				if(H1(i - mid, i - 1) == H2(i, i + mid - 1)) l = mid;
				else r = mid - 1;
			}
			ans = max(l * 2, ans);
		}
		printf("Case %d: %d\n", id, ans);
	}
	return 0;
}