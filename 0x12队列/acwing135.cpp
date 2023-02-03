#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 300010, INF = 0x3f3f3f3f;

int n, m;
int s[N];
deque<int> q;

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> s[i];
		s[i] += s[i - 1];
	}

	int ans = -INF;
	q.push_back(0);
	for(int i = 1; i <= n; i++) {
		while (!q.empty() && q.front() < i - m) q.pop_front();
		ans = max(ans, s[i] - s[q.front()]);
		while (!q.empty() && s[q.front()] >= s[i]) q.pop_back();
		q.push_back(i);
	}
	cout << ans;
	return 0;
}