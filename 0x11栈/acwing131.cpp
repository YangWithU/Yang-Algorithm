#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
typedef long long ll;

int top;
int a[N], stk[N], w[N];

void solve(int n) {
	memset(stk, 0, sizeof stk);
	for(int i = 1; i <= n; i++) cin >> a[i];

	ll ans = 0;
	a[n + 1] = top = 0;
	for(int i = 1; i <= n + 1; i++) {
		if(a[i] > stk[top]) {
			stk[++top] = a[i], w[top] = 1;
		} else {
			int totwid = 0;
			while (a[i] < stk[top]) {
				totwid += w[top];
				ans = max(ans, (ll)totwid * stk[top]);
				top--;
			}
			stk[++top] = a[i], w[top] = totwid + 1;
		}
	}
	cout << ans << endl;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n;
	while (cin >> n && n) solve(n);
	return 0;
}