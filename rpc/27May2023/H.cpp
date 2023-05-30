//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

vector<vector<int>> g;
vector<int> values;
vector<int> primes;
vector<int> posibilities;
vector<vector<ll>> dp,h,f;
vector<int> divisor;
vector<int> id(10001);

void calcPrimes(int n = 100){
	vector<int> toCheck(n+1,1);
	toCheck[0] = toCheck[1] = 0;

	for(int i = 2; i <= n;++i){
		if(toCheck[i]){
			primes.pb(i);
			for(int j = i*i; j <= n;j += i) toCheck[j] = 0;
		}
	}
}

void getPossibilities(int n){
	divisor.resize(2*n + 1,-1);
	for(auto &prime:primes){
		for(int i = prime; i < divisor.size(); i += prime) divisor[i] = prime;
	}
	for(int i = 2; i < divisor.size();++i){
		int temp = i;
		while(temp != 1 && divisor[temp] != -1){
			temp /= divisor[temp];
		}
		if(temp == 1){
			id[i] = posibilities.size();
			posibilities.pb(i);
		}
	}
}

void hh(int node){
	for(auto posi: posibilities){
		int val = dp[node][id[posi]];
		while(posi != 1){
			h[node][id[divisor[posi]]] = min(h[node][id[divisor[posi]]],val);
			posi /= divisor[posi];
		}
	}
}

void ff(int node){
	for(auto va: posibilities){
		int temp = va;
		while(temp != 1){
			f[node][id[va]] = min(h[node][id[divisor[temp]]],f[node][id[va]]);
			temp /= divisor[temp];
		}
	}
}

void go(int node, int dad){
	for(auto adj: g[node]){
		if(adj != dad){
			go(adj,node);
			hh(adj);
			ff(adj);
		}
	}
	for(auto posi: posibilities){
		int ans = (values[node] != posi ? posi : 0);
		for(auto adj:g[node]){
			if(adj != dad)
				ans += f[adj][id[posi]];
		}
		dp[node][id[posi]] = ans;
	}
}

int main(){
	ios_base::sync_with_stdio(0),cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n; cin >> n;

	calcPrimes();
	getPossibilities(n);
	g.resize(n);
	values.resize(n);

	for(auto &va: values) cin >> va;


	for(int i = 0; i < n-1;++i){
		int a,b; cin >> a >> b;
		--a,--b;
		g[a].pb(b);
		g[b].pb(a);
	}

	dp.resize(n,vector<int>(posibilities.size(),-1));
	h.resize(n,vector<int>(posibilities.size(),INT_MAX));
	f.resize(n,vector<int>(posibilities.size(),INT_MAX));

	go(0,-1);

	int ans = INT_MAX;

	for(auto va: posibilities)
		ans = min(ans,dp[0][id[va]]);

	cout << ans << "\n";

	return 0;
}