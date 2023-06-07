// I love Manuela
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
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


struct suffix_automaton{
	struct node {
		ll len, link, cnt, first_pos; bool end;
		map<char,int> next;
	};
	vector<node> sa;
	int last;
	suffix_automaton() {}
	suffix_automaton(string &s){
		sa.reserve(s.size()*2);
		last = add_node();
		sa[last].len = sa[last].cnt = sa[last].first_pos = sa[last].end = 0;
		sa[last].link = -1;
		for(char c : s) sa_append(c);
		mark_suffixes();
		build_cnt(0);
	}
	int add_node(){
		sa.push_back({});
		return sa.size()-1;
	}
	void mark_suffixes(){
		for(int cur = last; cur; cur = sa[cur].link)
			sa[cur].end = 1;
	}
	void sa_append(char c){
		int cur = add_node();
		sa[cur].len = sa[last].len + 1;
		sa[cur].end = sa[cur].cnt = 0;
		sa[cur].first_pos = sa[cur].len-1;
		int p = last;
		while(p != -1 && !sa[p].next[c]) {
			sa[p].next[c] = cur;
			p = sa[p].link;
		}
		if(p == -1) sa[cur].link = 0;
		else {
			int q = sa[p].next[c];
			if(sa[q].len == sa[p].len+1) sa[cur].link = q;
			else {
				int clone = add_node();
				sa[clone] = sa[q];
				sa[clone].len = sa[p].len+1;
				sa[clone].cnt = 0;
				sa[q].link = sa[cur].link = clone;
				while(p != -1 && sa[p].next[c] == q) {
					sa[p].next[c] = clone;
					p = sa[p].link;
				}
			}
		}
		last = cur;
	}

	ll build_cnt(int v) {
		if(sa[v].cnt)
			return sa[v].cnt;

		ll rta = sa[v].end;
		for(auto adj: sa[v].next)
			rta += build_cnt(adj.ss);

		return sa[v].cnt = rta;
	}
	node& operator[](int i) { return sa[i]; }
};


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	string imp; cin >> imp;

	suffix_automaton SAM(imp);

	int q; cin >> q;

	while(q--){
		string temp; cin >> temp;
		int sz = temp.size();
		temp = temp + temp;
		Hash h(temp);
		unordered_set<ll> seen;
		int ans = 0;

		for(int i = 0, now = 0, actSz = 0; i < temp.size()-1; ++i){
			while(now && !SAM[now].next.count(temp[i])){
				now = SAM[now].link;
			    actSz = SAM[now].len;
			}
			if(SAM[now].next.count(temp[i])) now = SAM[now].next[temp[i]], ++actSz;
			if(actSz >= sz && now && !seen.count(h.get(i-sz+1,i+1))){
				seen.insert(h.get(i-sz+1,i+1));
				while(SAM[SAM[now].link].len >= sz){
					now = SAM[now].link;
				    actSz = SAM[now].len;
				}
				if(actSz >= sz)
					ans += SAM[now].cnt;
			}
		}

		cout << ans << endl;
	}

	return 0;
}
