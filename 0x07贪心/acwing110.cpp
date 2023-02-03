#include <bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= int(n); ++i)
using namespace std;
const int N = 2510;

int c, l;
pair<int, int> pr[N];
map<int, int> spf;

int main()
{
	scanf("%d%d", &c, &l);
	rep(i, c) scanf("%d%d", &pr[i].first, &pr[i].second);
	rep(i, l) {
		int x, y; scanf("%d%d", &x, &y);
		spf[x] += y;
	}

	sort(pr + 1, pr + c + 1);

	spf[0] = spf[1001] = c;
	int cnt = 0;
	for(int i = c; i >= 1; i--) {
		auto cur = spf.upper_bound(pr[i].second);
		cur--;
		if(cur->first >= pr[i].first) {
			cnt++;
			if(--cur->second == 0)
				spf.erase(cur);
		}
	}
	printf("%d", cnt);
	return 0;
}