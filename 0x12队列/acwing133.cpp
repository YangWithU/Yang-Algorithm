#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 100010;
const ll INF = 0x3f3f3f3f3f3f3f3f;

priority_queue<int> pq;
queue<int> q1, q2;
int n, m, q, u, v, t, delta = 0;

int main()
{
	cin >> n >> m >> q >> u >> v >> t;
	for(int i = 1; i <= n; i++) {
		ll x; cin >> x;
		pq.push(x);
	}
	for(int i = 1; i <= m; i++) {
		ll mx = -INF;
		int op;
		if(!pq.empty() && mx < pq.top()) {
			mx = pq.top();
			op = 0;
		}
		if(!q1.empty() && mx < q1.front()) {
			mx = q1.front();
			op = 1;
		}
		if(!q2.empty() && mx < q2.front()) {
			mx = q2.front();
			op = 2;
		}
		if(op == 1) q1.pop();
		else if(op == 2) q2.pop();
		else pq.pop();
		mx += delta;
		q1.push(mx * u / v - delta - q);
		q2.push(mx - mx * u / v - delta - q);
		delta += q;
		if(i % t == 0) cout << mx << " ";
	}
	cout << endl;
	for(int i = 1; i <= n + m; i++) {
		ll mx = -INF;
		int op;
		if(!pq.empty() && mx < pq.top()) {
			mx = pq.top();
			op = 0;
		}
		if(!q1.empty() && mx < q1.front()) {
			mx = q1.front();
			op = 1;
		}
		if(!q2.empty() && mx < q2.front()) {
			mx = q2.front();
			op = 2;
		}
		if(op == 1) q1.pop();
		else if(op == 2) q2.pop();
		else pq.pop();
		if(i % t == 0) cout << mx + delta << " ";
	}
	cout << endl;
	return 0;
}