#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6010;

ll f[N][N];

int main()
{
	ios::sync_with_stdio(false); cin.tie(nullptr);
	int n; cin >> n;

	f[0][0] = 1;

	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n - i; j++)
			if(i || j)
				f[i][j] = (i ? f[i - 1][j + 1] : 0) + (j ? f[i][j - 1] : 0);
	cout << f[n][0] << endl;
	return 0;
}