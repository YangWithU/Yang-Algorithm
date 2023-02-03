#include <bits/stdc++.h>
using namespace std;
const int N = 1010;

int n;
pair<int, int> pr[N];

vector<int> mul(vector<int> a, int b) {
	vector<int> res;
	int t = 0;
	for(int i = 0; i < a.size(); ++i) {
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
	for(int i = a.size() - 1; i >= 0; --i) {
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

vector<int> maxVec(vector<int> a, vector<int> b) {
	if(a.size() > b.size()) return a;
	if(a.size() < b.size()) return b;
	// 数字长度相同，则逐位比较
	// 存储时低位在前，高位在后所以反向比较
	if(vector<int>(a.rbegin(), a.rend()) > vector<int>(b.rbegin(), b.rend()))
		return a;
	return b;
}

int main()
{
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		pr[i] = {x * y, x};
	}

	sort(pr + 1, pr + n + 1);

	vector<int> bigNum(1, 1);
	vector<int> res(1, 0);

	for(int i = 0; i <= n; ++i) {
		if(i) res = maxVec(res, div(bigNum, pr[i].first / pr[i].second));
		bigNum = mul(bigNum, pr[i].second);
	}

	for(int i = res.size() - 1; i >= 0; --i) printf("%d", res[i]);
	return 0;
}