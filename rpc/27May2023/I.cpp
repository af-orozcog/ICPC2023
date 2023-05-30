//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

int main(){
	ios_base::sync_with_stdio(0),cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n,m; cin >> n >> m;
	vector<vector<ll>> vals(n);

	for(int i = 0; i < n;++i){
		int upTo = min(m,n-i) + 1;
		for(int j = 0; j < upTo;++j){
			ll toAdd; cin >> toAdd;
			vals[i].pb(toAdd);
		}
	}

	vector<ll> dp(n);
	dp[0] = vals[0][0];
	for(int i = 1; i < n;++i){
		dp[i] = LLONG_MAX;
		for(int j = 1; j <= m && i - j >= 0;++j)
			dp[i] = min(dp[i],vals[i][0] + dp[i-j] - vals[i-j][j]);
	}

	ll ans = LLONG_MAX;

	for(int i = 1; i <= m && n - i > -1 ;++i){
		ans = min(ans,dp[n-i] - vals[n-i][i]);
	}
 
	cout << ans << "\n";

	return 0;
}