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
string solve(vector <int>& a, int d0) {
	int n = a.size();
	vector <int> b((n + 1)/2);
	b[0] = d0;

	int m = (n + 1) / 2;
	//cout << m << endl;
	for (int i = 1; i < m; i++) {
		int sum = 0;
		for (int j = 0; j < i; j++) sum += b[j]*b[i - j];
		sum %= 10;

		int bi = -1;
		for (int j = 9; j >= 0; j--) {
			if ((sum + 2*j*b[0]%10)%10 == a[i]) {
				bi = j;
				break;
			}
		}
		if (bi == -1) return string(100, '9');
		b[i] = bi;

	}

	for (int i = m; i < n; i++) {
		int ai = 0;
		for (int j = m - 1; i - j < m; j--) { 
			ai += b[j]*b[i - j];
		}
		ai %= 10;
		if (ai != a[i]) return string(100, '9');
	}

	string ans = "";
	for (int i = b.size() - 1; i >= 0; i--) ans += char(b[i] + '0');
	return ans;
}
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	string s; cin >> s;
	if (s.size()%2 == 0) {
		cout << -1 << endl;
		return 0;
	}
	vector <int> a(s.size());
	for (int i = 0; i < (int)s.size(); i++) a[i] = s[i] - '0';
	reverse(a.begin(), a.end());

	string ans = string(100, '9');
	for (int i = 1; i < 9; i++) {
		if (i*i % 10 != a[0]) continue;
		ans = min(ans, solve(a, i));
	}
	if (ans.size() > s.size()) ans = "-1";
	cout << ans << endl;
	return 0;
}
