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

using namespace std;
/* *
 *
 * Too many mind, no mind.
 *
 * */
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a%b); }
long long lcm(long long a, long long b) { return a / gcd(a, b)*b; }
struct frac{
	long long x, y;
	frac norm(long long nx, long long ny) {
		long long g = gcd(nx, ny);
		return {nx/g, ny/g};
	}
	frac operator * (const frac& b) {
		long long nx = x*b.x, ny = y*b.y;
		return norm(nx, ny);
	}
	frac operator + (const frac& b) {
		long long l = lcm(y, b.y);
		long long nx = x*(l/y) + b.x*(l/b.y), ny = l;
		return norm(nx, ny);
	}
	
};
template <class T> struct Matrix {
	vector <vector <T>> m;
	int N, M;
	Matrix (bool identity, int rows, int columns) {
		N = rows; M = columns;
		m.resize(N, vector <T> (M, {0, 1}));
		if (identity && N == M) {
			for (int i = 0; i < N; i++) m[i][i] = {1, 1};
		}
	}
	Matrix operator * (const Matrix &o) {
		Matrix <T> r(false, N, o.M);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < o.M; j++) {
				for (int k = 0; k < M; k++) {
					r.m[i][j] = m[i][k]*o.m[k][j] + r.m[i][j];
				}
			}
		}
		return r;
	}

	friend Matrix binpow(Matrix <T> o, long long r) {
		 Matrix <T> ans(true, o.N, o.N); 
		 for (; r; o = o*o, r >>= 1) {
			 if (r &1) ans = ans*o;
		 }
		 return ans;
	}
};
int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	long long n; cin >> n;
	Matrix <frac> m(0, 2, 2);
	frac h = {1, 2}, z = {0, 2}, o = {1, 1};
	m.m = {{h, h}, 
		{o, z}};

	cout << fixed << setprecision(10);
	if (n == 1) cout << 100.0 << ' ' << 0.0 << endl;
	else if (n == 2) cout << 0.0 << ' ' << 100.0 << endl;
	else if (n >= 50) cout << 33.3333333333 << ' ' << 66.6666666667 << endl;
	else {
		frac c = {100, 1};
		Matrix <frac> fib = binpow(m, n - 2);
		Matrix <frac> v(0, 2, 1);
		v.m = {{c}, {z}};
		Matrix <frac> ans = fib*v;
		long double x = double(ans.m[0][0].x) / double(ans.m[0][0].y);
		cout << 100.0 - x << ' ' << x << endl;
	}
	return 0;
}

