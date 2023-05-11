// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

/// Complexity: O(|N|*log(|alphabet|))
/// Tested: https://tinyurl.com/y7cevdeg
struct suffix_automaton {
  struct node {
    int len, link, cnt, first_pos; bool end; /// cnt is endpos size, first_pos is minimum of endpos
    map<int,int> gotHere;
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
    build_cnt();
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
  /// This is O(N*log(N)). Can be done O(N) by doing dfs and counting paths to terminal nodes.
  void build_cnt() {
    vector<int> order(sa.size()-1);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int a, int b) { return sa[a].len > sa[b].len; });
    for(auto &i : order) sa[ sa[i].link ].cnt += sa[i].cnt;
    sa[0].cnt = 0; /// t0 is empty string 
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

vector<bool> marked;
int getAns(int now,suffix_automaton &SA, int amount){
  int ans = 0;
  if(SA[now].gotHere.size() == amount){
    int temp = INT_MAX;
    for(auto &va:SA[now].gotHere)
      temp = min(va.ss,temp);
    ans = temp;
  }
  for(auto &va:SA[now].next){
    if(!marked[va.ss])
      ans = max(ans,getAns(va.ss,SA,amount));
  }
  return ans;
}

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  vector<string> see;

  string temp;
  while(getline(cin,temp)){
    see.pb(temp);
  }

  suffix_automaton SA(see[0]);

  for(int i = 1; i < see.size();++i){
    int now = 0, l = 0;
    for(int j = 0; j < see[i].size();++i){
      
    }
  }

  return 0;
}