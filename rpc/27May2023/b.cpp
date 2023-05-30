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
struct mbm {
	int l, r;
	vector <vector<int>> g;
	vector <int> match, seen;
	mbm(int l, int r) : l(l), r(r) { 
		seen.resize(r); 
		match.resize(r); 
		g.resize(l); 
	}

	void addedge(int l, int r) { g[l].push_back(r); }
	bool dfs(int u) {
		for(auto v : g[u]) {
			if (seen[v]++) continue;
			if (match[v] == -1 || dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
		return false;
	}
	int max_matching() {
		int ans = 0;
		fill(match.begin(), match.end(), -1);
		for (int u = 0; u < l; u++) {
			fill(seen.begin(), seen.end(), 0);
			ans += dfs(u);
		}
		return ans;
	}
};
const int maxn = 2e7 + 20, maxm = 1010;
int n;
bool sieve[maxn];
int a[maxm];
int main() {
	//ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	sieve[0] = sieve[1] = 1;
	for (int i = 0; i < maxn; i++) {
		if (sieve[i]) continue;
		for (int j = i + i; j < maxn; j += i) sieve[j] = 1;
	}
	
	scanf("%d ",&n);
	int cnt = 0;
	for (int i=0; i < n; i++) {
		scanf("%d ", &a[i]);
		if (a[i] == 1) cnt++;
	}
	int one = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			one = i;
			break;
		}
	}

	mbm net(n+10, n+10);

	for (int i = 0; i < n; i++) {
		if (a[i]&1) continue;

		for (int j= 0; j < n; j++) {
			if (a[j] == 1) continue;
			if (!sieve[a[i] + a[j]]) net.addedge(i, j);
		}
		if (one != -1 && !sieve[a[i] + a[one]]) net.addedge(i, one);
	}

	int total = n - cnt + (one != -1);
	int ans = total - net.max_matching();
	printf("%d\n",ans);
	return 0;
}
