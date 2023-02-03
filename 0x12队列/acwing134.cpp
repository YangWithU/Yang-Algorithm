#include <bits/stdc++.h>
using namespace std;
const int N = 200010, INF = 0x3f3f3f3f;

int n;
pair<int, int> a[N];
vector<int> p[N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		a[i].first = x, a[i].second = i;
	}

	sort(a + 1, a + n + 1);

	int tt = 0;
	for(int i = 1; i <= n; i++) {
		p[++tt].push_back(a[i].second);
		while (a[i].first == a[i + 1].first)
			p[tt].push_back(a[++i].second);
	}

	for(int i = 1; i <= tt; i++) sort(p[i].begin(), p[i].end());

	bool flag = false;
	int num = INF, ans = 1;
	for(int i = 1; i <= tt; i++) {
		int s = p[i].size();
		if(flag) {
			if(num < p[i][0]) num = p[i][s - 1];
			else {
				++ans;
				flag = false;
				num = p[i][0];
			}
		} else {
			if(num > p[i][s - 1]) num = p[i][0];
			else {
				flag = true;
				num = p[i][s - 1];
			}
		}
	}
	cout << ans;
	return 0;
}