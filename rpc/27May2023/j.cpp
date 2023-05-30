#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>

using namespace std;
/* *
 *
 * Too many mind, no mind.
 *
 * */
const int maxn = 1e5 + 10;
int n;
int a[maxn];
int dp[maxn][20][5];
bool memo[maxn][20][5];
int go(int i, int mask, int prev) {
	if (i >= n) return 0;
	int& ans = dp[i][mask][prev];
	if (memo[i][mask][prev]) return ans;

	ans = go(i + 1, mask, prev);
	if (a[i] == prev) ans = max(ans, go(i + 1, mask, prev) + 1);
	else if (!((mask >> a[i]) & 1)) {
		ans = max(ans, go(i + 1, mask | (1 << a[i]), a[i]) + 1);
	}

	memo[i][mask][prev] = 1;
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string s; cin >> s;
	n = s.size();
	for (int i =0; i < n; i++) {
		if (s[i] == 'h') a[i] = 0;
		if (s[i] == 'c') a[i] = 1;
		if (s[i] == 'd') a[i] = 2;
		if (s[i] == 's') a[i] = 3;
	}
	cout << n - go(0, 0, 4) << endl;
	return 0;
}
