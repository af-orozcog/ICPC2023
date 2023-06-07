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
const int maxn = 2e5 + 10, oo = 1e9;
int last[maxn];
vector <int> pos[maxn];
struct SegmentTree {
	int n;
	vector <int> tree;
	SegmentTree (int n) :n(n) {
		tree.assign((n + 1) << 1, oo);
	}
	void update(int k, int x) {
		k += n;
		tree[k] = x;
		for (k >>= 1; k; k >>= 1) tree[k] = min(tree[k << 1], tree[k << 1 | 1]);
	}
	int query(int l, int r) {
		int ans = oo;
		l += n, r+= n;
		while (l <= r) {
			if (l & 1) ans = min(ans, tree[l++]);
			if (!(r & 1)) ans = min(ans, tree[r--]);
			l >>= 1, r >>= 1;
		}
		return ans;
	}
};
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n, k; cin >> n >> k;
	vector <int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		pos[a[i]].push_back(i);
		last[a[i]] = i;
	}
	SegmentTree seg(k + 5);
	set <int> rem;
	for (int i = 0; i < k; i++) {
		reverse(pos[i].begin(), pos[i].end());
		rem.insert(last[i]);
		seg.update(i, pos[i].back());
	}

	for (int l = 0, done = 0; l < n && done < k; ) {
		int lo = 0, hi = k - 1;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (seg.query(0, mid) <= *rem.begin()) hi = mid;
			else lo = mid + 1;
		}
		rem.erase(last[lo]);
		cout << lo + 1 << ' ';
		done++;
		int r = pos[lo].back();
		while (l <= r) {
			pos[a[l]].pop_back();
			if (pos[a[l]].size()) {
				int val = seg.query(a[l], a[l]);
				seg.update(a[l], max(val, pos[a[l]].back()));
			}
			l++;
		}
		seg.update(lo, oo);
	}
	cout << endl;
	return 0;
}
