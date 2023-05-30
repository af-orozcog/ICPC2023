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
const int maxn = 2e7 + 5, maxm = 751;
vector <int> g[maxm];
bool used[maxm];
int mt[maxm];
int ans;

bool kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < (int) g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == 0 || kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }   
    return false;
}
int n;
int sieve[maxn];
int a[maxm];
int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	sieve[0] = sieve[1] = 1;
	for (int i = 2; i < maxn; i++) {
		if (sieve[i]) continue;
		for (int j = i + i; j < maxn; j += i) sieve[j] = 1;
	}
	cin >> n;
	int cnt = 0;
	for (int i=0; i < n; i++) {
		cin >> a[i];
		if (a[i] == 1) cnt++;
	}


	int one = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			one = i;
			break;
		}
	}


	for (int i = 0; i < n; i++) {
		if (a[i]&1) continue;

		for (int j= 0; j < n; j++) {
			if (a[j] == 1) continue;
			if (!sieve[a[i] + a[j]]) g[i].push_back( j);
		}
		if (one != -1 && !sieve[a[i] + a[one]]) g[i].push_back(one);
	}

	int total = n - cnt + (one != -1);
	int match = 0;
	for (int i = 0; i < n; i++) {
		if (a[i]&1) continue;
        memset(used, 0, sizeof(used));
        if (kuhn(i))
            match++;
	}
	ans = total - match;

	cout << ans << endl;
	return 0;
}

