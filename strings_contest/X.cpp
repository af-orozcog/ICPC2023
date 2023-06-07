// I love Manuela
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;

#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

struct Hash {
	int P=1777771,MOD[2],PI[2];
	vector<int> h[2],pi[2];
	Hash(string& s){
		MOD[0]=999727999;MOD[1]=1070777777;
		PI[0]=325255434;PI[1]=10018302;
		fore(k,0,2)h[k].resize(s.size()+1),pi[k].resize(s.size()+1);
		fore(k,0,2){
			h[k][0]=0;pi[k][0]=1;
			ll p=1;
			fore(i,1,s.size()+1){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
	ll get(int s, int e){
		ll h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
		h0=(1LL*h0*pi[0][s])%MOD[0];
		ll h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
	}
};


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int q; cin >> q;

	unordered_set<ll> seen;
	map<int,int> sizes;
	while(q--){
		int t; string check;
		cin >> t >> check;
		if(t == 1){
			Hash see(check);
			sizes[check.size()]++;
			seen.insert(see.get(0,check.size()));
		} else if(t == 2){
			Hash see(check);
			--sizes[check.size()];
			if(!sizes[check.size()]) sizes.erase(check.size());
			seen.erase(see.get(0,check.size()));
		} else {
			if(!sizes.size()) {
				cout << 0 << endl;
				continue;
			}
			Hash see(check);
			int ans = 0;
			int smallest = sizes.begin()->ff;
			for(int i = smallest; i <= check.size();++i){
				for(auto &va: sizes){
					if(va.ff <= i + 1){
						ans += seen.count(see.get(i-va.ff,i));
					} else break;
				}
			}

			cout << ans << endl;
		}
	}
	return 0;
}