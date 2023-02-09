#include <bits/stdc++.h>
using namespace std;
const int N = 200010;

int n;
string s;

int main()
{
	// 注意本题字符串下标从0开始
	ios::sync_with_stdio(false); cin.tie(nullptr);
	scanf("%d", &n);
	string cur;
	while (cin >> cur) s += cur;
	s += s;

	int i = 0, j = 1;
	while (i < n && j < n) {
		int k = 0;
		while (k < n && s[i + k] == s[j + k]) k++;
		if(k == n) break;
		if(s[i + k] > s[j + k]) {
			i = i + k + 1;
			if(i == j) i++;
		} else {
			j = j + k + 1;
			if(i == j) j++;
		}
	}
	printf("%d", min(i, j));
	return 0;
}