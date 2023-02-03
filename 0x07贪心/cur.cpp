#include <bits/stdc++.h>
using namespace std;
const int N = 1010;

int n;
pair<int, int> pr[N];
vector<int> mul(vector<int> a, int b) {
	vector<int> res;
	int t = 0;
	for(int i = 0; i < a.size(); i++) {
		t += a[i] * b;
		res.push_back(t % 10);
		t /= 10;
	}
	while (t) {
		res.push_back(t % 10);
		t /= 10;
	}
	return res;
}

vector<int> div(vector<int> a, int b) {
	vector<int> res;
	bool is_first = true;
	int t = 0;
	for(int i = a.size() - 1; i >= 0; i--) {
		t = t * 10 + a[i];
		int x = t / b;
		if(!is_first || x) {
			is_first = false;
			res.push_back(x);
		}
		t %= b;
	}
	reverse(res.begin(), res.end());
	return res;
}

vector<int> max_vec(vector<int> a, vector<int> b) {
	if(a.size() > b.size()) return a;
	if(a.size() < b.size()) return b;
	if(vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend())) 
		return a;
	return b;
}

int main()
{
	scanf("%d", &n);
	// 将国王也纳入pr中
	for(int i = 0; i <= n; i++) {
		int a, b; scanf("%d%d", &a, &b);
		pr[i] = make_pair(a * b, a);
	}

	sort(pr + 1, pr + n + 1);

	vector<int> bigNum(1, 1);
	vector<int> res(1, 0);

	for(int i = 0; i <= n; i++) {
		if(i) res = max_vec(res, div(bigNum, pr[i].first / pr[i].second));
		bigNum = mul(bigNum, pr[i].second);
	}
	for(int i = res.size() - 1; i >= 0; i--) printf("%d", res[i]);
	return 0;
}