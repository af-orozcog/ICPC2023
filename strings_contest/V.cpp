// I love Manuela
#include<bits/stdc++.h>
#define ll long long 
#define ff first
#define ss second
#define pb push_back
using namespace std;

struct suffix_automaton {
	struct node {
		ll len, link, cnt, first_pos; bool end;
		ll total = 0;
		map<char,int> next;
	};
	vector<node> sa;
	int last;
	suffix_automaton(){}
	suffix_automaton(string &s){
		sa.reserve(s.size()*2);
		last = add_node();
		sa[last].len = sa[last].cnt = sa[last].first_pos = sa[last].end = 0;
		sa[last].link = -1;
		for(char c : s) sa_append(c);
		mark_suffixes();
		build_cnt(0);
		build_total(0);
	}
	int add_node(){
		sa.pb({});
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
		while(p != -1 && !sa[p].next[c]){
			sa[p].next[c] = cur;
			p = sa[p].link;
		}
		if(p == -1) sa[cur].link = 0;
		else {
			int q = sa[p].next[c];
			if(sa[q].len == sa[p].len+1) sa[cur].link = q;
			else{
				int clone = add_node();
				sa[clone] = sa[q];
				sa[clone].len = sa[p].len+1;
				sa[clone].cnt = 0;
				sa[q].link = sa[cur].link = clone;
				while(p != -1 && sa[p].next[c] == q){
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
	ll build_total(int v){
		if(sa[v].total)
			return sa[v].total;
		ll rta = sa[v].cnt;
		for(auto adj: sa[v].next)
			rta += build_total(adj.ss);
		return sa[v].total = rta;
	}

	node& operator[] (int a) {return sa[a];}
};



int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	string imp; cin >> imp;

	suffix_automaton SAM(imp);
	string ans = "";
	ll check; cin >> check;
	int now = 0;

	while(check > 0) {
		int bef = now;
		for(auto adj: SAM[now].next){
			if(SAM[adj.ss].total >= check){
				check -=  SAM[adj.ss].cnt;
				now = adj.ss;
				ans += adj.ff;
				break;
			} else {
				check -= SAM[adj.ss].total;
			}
		}
		if(bef == now) break;
	}

	cout << (check > 0 ? "No such line." : ans) << "\n";

	return 0;
}