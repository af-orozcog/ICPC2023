// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

const static int N = 2*1000000+2;
const static int alpha = 26;
int trie[N][alpha], fail[N], nodes;
vector<int> endWord(N,INT_MAX);
void add(string &s, int i) {
  int cur = 0;
  for(char c : s) {
    int x = c-'a';
    if(!trie[cur][x]) trie[cur][x] = ++nodes;
    cur = trie[cur][x];
  }
  //cnt_word[cur]++;
  endWord[cur] = min(i,endWord[cur]); // for i > 0
}
void build() {
  queue<int> q; q.push(0);
  while(q.size()) {
    int u = q.front(); q.pop();
    endWord[u] = min(endWord[u],endWord[fail[u]]);
    for(int i = 0; i < alpha; ++i) {
      int v = trie[u][i];
      if(!v) trie[u][i] = trie[ fail[u] ][i]; // construir automata
      else q.push(v);
      if(!u || !v) continue;
      fail[v] = trie[ fail[u] ][i];
      //fail_out[v] = end_word[ fail[v] ] ? fail[v] : fail_out[ fail[v] ];
      //cnt_word[v] += cnt_word[ fail[v] ]; // obtener informacion del fail_padre
    }
  }
}

int getAns(string &check){
    int v = 0;
    int ans = INT_MAX;
    for(auto let:check){
        int next = trie[v][let-'a'];
        ans = min(ans,endWord[next]);
        v = next;
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	  //freopen("input.txt", "r", stdin);
	  //freopen("output.txt", "w", stdout);

    int n; cin >> n;
    vector<pair<int,string>> check(n);
    for(auto &va:check){
        cin >> va.ff >> va.ss;
    }

    for(int i = 0; i < n;++i){
        if(check[i].ff == 0)
            add(check[i].ss,i);
    }

    build();

    for(int i = 0; i < n;++i){
        if(check[i].ff == 1){
            int see = getAns(check[i].ss);
            if(see < i) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}