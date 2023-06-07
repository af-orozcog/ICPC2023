// I love Manuela
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back

using namespace std;

/// Complexity: O(|N|*log(|alphabet|))
/// Tested: https://tinyurl.com/y7cevdeg
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
    sa[cur].end = 0; sa[cur].cnt = 1;
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
  node& operator[](int i) { return sa[i]; }
};

vector<vector<ll>> dp;

ll go(int p, int n, suffix_automaton &SAM, char good){
	if(dp[p][n] != -1) return dp[p][n];
	ll ans = 0;

	for(auto adj: SAM[n].next){
	    if(adj.ff == good) ans += 1;
	    else if (isdigit(adj.ff)) continue;
		else ans += go(p,adj.ss,SAM,good);
	}

	return dp[p][n] = ans;
}

const ll MOD = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	vector<string> vals(3); cin >> vals[0] >> vals[1] >> vals[2];
	string send = vals[0] + "1" + vals[1] + "2" + vals[2] + "3";

	suffix_automaton SAM(send);

	dp.resize(3,vector<ll>(SAM.sa.size(),-1));

	for(int i = 0; i < 3;++i){
		for(int j = 0; j < SAM.sa.size();++j){
			go(i,j,SAM,i+1+'0');
			if(dp[i][j] >= MOD) dp[i][j] %= MOD;
		}
	}
	
	vector<ll> plus(min(vals[0].size(),min(vals[1].size(),vals[2].size()))+2);
  vector<ll> mini(min(vals[0].size(),min(vals[1].size(),vals[2].size()))+2);

	for(int i = 1; i < SAM.sa.size();++i){
		ll add = 1;
		for(int j = 0; j < 3;++j){
		    ll wut = dp[j][i];
			add *= dp[j][i];
			if(add >= MOD) add %= MOD;
		}
		if(add == 0) continue;
		int left = SAM[SAM[i].link].len + 1;
		int right = SAM[i].len;
		plus[left] += add;
		if(plus[left] >= MOD) plus[left] -= MOD;
		mini[right+1] += add;
		if(mini[right+1] >= MOD) mini[right+1] -= MOD;
	}

	ll temp = 0;
	int upTo = min(vals[0].size(),min(vals[1].size(),vals[2].size()));
	for(int i = 1; i <= upTo; ++i){
		temp += plus[i];
		if(temp >= MOD) temp -= MOD;
		temp -= mini[i];
		if(temp < 0) temp += MOD;
		cout << temp << ' ';
	}

	cout << endl;
	return 0;
}