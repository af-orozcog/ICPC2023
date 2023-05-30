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
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector <vector<int>> a(2, vector<int>(n, 0)); 
	vector <int> known(n);
	for (int i = 0; i < n;i++) {
		if (s[i] == 'L') a[0][i] = 1;
		else a[1][i] = 1;
	}

	int ans  = 0;
	for (int i = 0; i < k; i++) {
		int prev = 1, j = 0;
		for (j = 0 ; j < n; j++) {
			if (known[j]) {
				prev = (a[0][j] == 1 ? 0 : 1);
			} else {
				known[j] = 1;
				if (a[1 - prev][j]) {
					prev = 1 - prev;
				} else break;
			}
		}
		ans += j >= n;
	}
	cout << ans << endl;
	return 0;
}
