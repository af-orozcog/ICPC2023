//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;


struct info { int val;};
info merge(info &a, info &b){
	return {a.val + b.val};
}

info NEUTRAL = {0};

struct segtree{
	int n;
	vector<info> t;
	segtree(int n, vector<int> &v): n(n), t(2*n){
		for(int i = 0; i < n;++i) t[i+n] = {v[i]};
		for(int i = n-1; i; --i) t[i] = merge(t[i<<1],t[i<<1|1]);
	}

	info query(int l, int r){
		info ans_l = NEUTRAL, ans_r = NEUTRAL;
		for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1){
			if(l&1) ans_l = merge(ans_l, t[l++]);
			if(r&1) ans_r = merge(t[--r], ans_r);
		}
		return merge(ans_l,ans_r);
	}

	void modify(int p, int x){
		for(t[p += n] = {x}; p >>= 1; ) t[p] = merge(t[p<<1],t[p<<1|1]);
	}
};

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n,q; cin >> n >> q;

	vector<int> initial(n,1);
	segtree seg(n,initial);

	while(q--){
		char op; cin >> op;
		if(op == '-'){
			int a; cin >> a; --a;
			seg.modify(a,0);
		}else if(op == '+'){
			int a; cin >> a; --a;
			seg.modify(a,1);
		}
		else{
			int a,b; cin >> a >> b; --a,--b;
			if(a > b) swap(a,b);
			int val1 = seg.query(a,b).val;
			int val2 = seg.query(0,a).val + seg.query(b,n-1).val;
			if(seg.query(a,b).val == b-a+1) cout << "possible\n";
			else if(seg.query(0,a).val + seg.query(b,n-1).val == a + 1 + (n-b)) cout << "possible\n";
			else cout << "impossible\n";
		}
	}

	return 0;
}