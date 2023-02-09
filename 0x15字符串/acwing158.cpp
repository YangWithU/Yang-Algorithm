#include <bits/stdc++.h>
using namespace std;

int getMin(string s) {
	int i = 0, j = 1, n = s.length() / 2;
	while (i < n && j < n) {
		int k = 0;
		while (k < n && s[i + k] == s[j + k]) k++;
		if(k == n) break;
		if(s[i + k] > s[j + k]) i = i + k + 1;
		else j = j + k + 1;
		if(i == j) i++;
	}
	return min(i, j);
}

int main()
{
	string a, b;
	cin >> a >> b;
	int n = a.length();
	a += a, b += b;

	int x = getMin(a), y = getMin(b);
	string ans1, ans2;
	for(int i = 0; i < n; i++)
		ans1 += a[i + x], ans2 += b[i + y];
	if(ans1 == ans2) cout << "Yes" << "\n" << ans1 << endl;
	else cout << "No" << endl;
	return 0;
}