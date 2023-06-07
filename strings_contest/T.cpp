// I love Manuela
#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct suffix_automaton {
	struct node {
	    int len, link, cnt, first_pos; bool end; /// cnt is endpos size, first_pos is minimum of endpos
	    map<char, int> next;
	  };
	  vector<node> sa;
	  int last;
	  suffix_automaton() {}
	  suffix_automaton(string &s) {
	    sa.reserve(s.size()*2);
	    last = add_node();
	    sa[last].len = sa[last].cnt = sa[last].first_pos = sa[last].end = 0;
	    sa[last].link = -1;
	    for(char c : s) sa_append(c);
	    mark_suffixes();
	    contar(0);
	  }
	  int add_node() {
	    sa.push_back({});
	    return sa.size()-1;
	  }
	  void mark_suffixes() {
	    ///t0 is not suffix
	    for(int cur = last; cur; cur = sa[cur].link)
	      sa[cur].end = 1;
	  }
	  void sa_append(char c) {
	    int cur = add_node();
	    sa[cur].len = sa[last].len + 1;
	    sa[cur].end = sa[cur].cnt = 0;
	    sa[cur].first_pos = sa[cur].len-1;
	    int p = last;
	    while(p != -1 && !sa[p].next[c] ){
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
	ll contar(int v){
		if(sa[v].cnt){
			return sa[v].cnt;
		}
		ll rta = sa[v].end;
		for ( auto const& x: sa[v].next)
			rta += contar(x.second);
		
		return sa[v].cnt = rta;
	}
	node& operator[](int i) {return sa[i];}
};


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int t; cin >> t;
	
	while(t--){
		string temp; cin >> temp;
		suffix_automaton SA(temp);
		ll ans = 0;
		for(int i = 1; i < SA.sa.size(); ++i)
			ans += SA[i].cnt * SA[i].cnt * (SA[i].len - SA[SA[i].link].len);
		cout << ans << endl;
	}

	return 0;
}
