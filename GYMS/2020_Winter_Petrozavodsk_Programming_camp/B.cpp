// I love Manuela
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
#include <iomanip>

#define ll long long
using namespace std;


/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/y8g2q66b
namespace fft {
  const double PI = acos(-1.0);
  vector<int> rev;
  struct pt {
    double r, i;
    pt(double r = 0.0, double i = 0.0) : r(r), i(i) {}
    pt operator + (const pt & b) { return pt(r + b.r, i + b.i); }
    pt operator - (const pt & b) { return pt(r - b.r, i - b.i); }
    pt operator * (const pt & b) { return pt(r * b.r - i * b.i, r * b.i + i * b.r); }
  };
  void fft(vector<pt> &y, int on) {
    int n = y.size();
    for(int i = 1; i < n; i++) if(i < rev[i]) swap(y[i], y[rev[i]]);
    for(int m = 2; m <= n; m <<= 1) {
      pt wm(cos(-on * 2 * PI / m), sin(-on * 2 * PI / m));
      for(int k = 0; k < n; k += m) {
        pt w(1, 0);
        for(int j = 0; j < m / 2; j++) {
          pt u = y[k + j];
          pt t = w * y[k + j + m / 2];
          y[k + j] = u + t;
          y[k + j + m / 2] = u - t;
          w = w * wm;
        }
      }
    }
    if(on == -1)
      for(int i = 0; i < n; i++) y[i].r /= n;
  }
  vector<ll> mul(vector<ll> &a, vector<ll> &b) {
    int n = 1, la = a.size(), lb = b.size(), t;
    for(n = 1, t = 0; n <= (la+lb+1); n <<= 1, t++); t = 1<<(t-1);
    vector<pt> x1(n), x2(n);
    rev.assign(n, 0);
    for(int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 |(i & 1 ? t : 0);
    for(int i = 0; i < la; i++) x1[i] = pt(a[i], 0);
    for(int i = 0; i < lb; i++) x2[i] = pt(b[i], 0);
    fft(x1, 1); fft(x2, 1);
    for(int i = 0; i < n; i++) x1[i] = x1[i] * x2[i];
    fft(x1, -1);
    vector<ll> sol(n);
    for(int i = 0; i < n; i++) sol[i] = x1[i].r + 0.5;
    return sol;
  }
}

const ll MAX = 999993; 
vector<ll> F(1e6+1,0);


int main(){
	ios_base::sync_with_stdio(0),cin.tie(0);

	int t; cin >> t;

	for(int i = 1; i <= 1e6;++i){
		ll ans = 0;
		int temp = i;
		while(temp % 2 == 0){
			++ans;
			temp >>= 1;
		}
		F[i] = F[i-1] + ans;
	}

	while(t--){
		int n; cin >> n;
		vector<ll> seen(MAX+1); 
		vector<ll> check(n);
		for(auto &va: check){
			cin >> va;
			++seen[F[va]];
		}
		vector<ll> toMul(MAX+1);

		for(int i = 0; i <= 1e6;++i){
			++toMul[F[i]];
		}

		vector<ll> letSee = fft::mul(seen,toMul);

		ll ans = 0;

		for(auto va: check)
			ans += letSee[F[va]]/2;

		cout << ans << "\n";
	}

	return 0;		
}
