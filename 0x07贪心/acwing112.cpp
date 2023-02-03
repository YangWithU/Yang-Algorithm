#include <bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= int(n); ++i)
using namespace std;
const int N = 1010;
const double eps = 1e-6, INF = 1e10;

int n, d;
bool flag = true;
pair<double, double> seg[N];

int main()
{
	scanf("%d%d", &n, &d);
	rep(i, n) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(y > d) {
			flag = false;
			break;
		}
		double len = sqrt(d * d - y * y);
		seg[i] = make_pair(x - len, x + len);
	}

	if(!flag) puts("-1");
	else {
		sort(seg + 1, seg + n + 1);
		double pos = -INF;
		int cnt = 0;
		rep(i, n) {
			if(seg[i].first > pos + eps) {
				pos = seg[i].second;
				cnt++;
			} else pos = min(seg[i].second, pos);
		}
		printf("%d", cnt);
	}
	return 0;
}