//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;



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

struct HashCustom {
	int P=1777771,MOD[2],PI[2];
	vector<int> h[2],pi[2];
	ll p1,p2;
	int sz = 0;
	HashCustom(int tama){
		MOD[0]=999727999;MOD[1]=1070777777;
		PI[0]=325255434;PI[1]=10018302;
		fore(k,0,2)pi[k].resize(tama+1);
		h[0].pb(0), h[1].pb(1);
		fore(k,0,2){
			pi[k][0]=1;
			ll p=1;
			fore(i,1,tama+1){
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
		p1 = p2 = 1;
	}

	void addLetter(char toAdd){
		++sz;
		h[0].pb((h[0].back()+p1*toAdd)%MOD[0]);
		h[1].pb((h[1].back()+p2*toAdd)%MOD[1]);
		p1 = (p1*P) % MOD[0];
		p2 = (p2*P) % MOD[1];
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
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

	string imp; cin >> imp;
	int q,a,b; cin >> q >> a >> b;

	set<int> sizes;
	vector<string> see(q);

	for(auto &va:see){
		cin >> va;
		sizes.insert(va.size());
	}

	vector<int> ans;
	map<ll,int> co;

	HashCustom hs(imp.size()+q);
	char toAdd;

	for(int i = 0,j = 0; i < imp.size() + q;++i){
		if(i < imp.size())
			hs.addLetter(imp[i]);
		else
			hs.addLetter(toAdd);
		for(auto sz: sizes){
			int lel = hs.sz;
			if(hs.sz <= sz){
				++co[hs.get(hs.sz - sz,hs.sz)];
			}
			else break;
		}

		if(i >= (imp.size() - 1)){
			Hash h(see[j]);
			ans.pb(co[h.get(0,see[j].size())]);
			++j;
			toAdd = 'a' + ((a*ans.back() + b) % 26);
		}
	}


	for(auto va: ans)
		cout << va << "\n";

	return 0;
}