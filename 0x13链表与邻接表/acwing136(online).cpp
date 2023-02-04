#include <bits/stdc++.h>
using namespace std;
const int N = 100010, INF = 0x3f3f3f3f;

set<pair<int, int>> s;

int main()
{
	int n, a;
	cin >> n >> a;
	s.insert(make_pair(a, 1));
	for(int i = 2; i <= n; i++) {
		cin >> a;
		s.insert(make_pair(a, i));

		auto it = s.find(make_pair(a, i));
		pair<int, int> ans;
		ans.first = INF; // 防止第一种情况没找到无法进行第二种的情况
		if(++it != s.end()) // 在当前元素后面找
			ans = make_pair((*it).first - a, (*it).second);
		it = s.find(make_pair(a, i));
		// 在前面找
		if(it-- != s.begin() && ans.first >= a - (*it).first)
			ans = make_pair(a - (*it).first, (*it).second);
		cout << ans.first << " " << ans.second << endl;
	}
	return 0;
}