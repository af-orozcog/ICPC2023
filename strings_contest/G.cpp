// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

struct info { int val; };
info merge(info &a, info &b) {
  return {min(a.val,b.val)};
}
info NEUTRAL = {INT_MAX};
struct segtree { // for point update and range queries, supports left to right merge
  int n; /// 0-indexed
  vector<info> t;
  segtree(int n, vector<int> &v) : n(n), t(2*n) {
    for(int i = 0; i < n; i++) t[i+n] = {v[i]};
    for(int i = n-1; i > 0; --i) t[i] = merge(t[i<<1], t[i<<1|1]);
  } 
  info query(int l, int r) {
    info ans_l = NEUTRAL, ans_r = NEUTRAL;
    for(l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
      if(l&1) ans_l = merge(ans_l, t[l++]);
      if(r&1) ans_r = merge(t[--r], ans_r);
    }
    return merge(ans_l, ans_r);
  }
  void modify(int p, int x) {
    for(t[p += n] = {x}; p >>= 1; ) t[p] = merge(t[p<<1], t[p<<1|1]);
  }
};

const int alpha = 400; 
struct suffix_array { // s MUST not have 0 value
  vector<int> sa, pos, lcp;
  suffix_array(string s) {
    s.push_back('$'); // always add something less to input, so it stays in pos 0
    int n = s.size(), mx = max(alpha, n)+2;
    vector<int> a(n), a1(n), c(n+1), c1(n+1), head(mx), cnt(mx);
    pos = lcp = a;
    for(int i = 0; i < n; i++) c[i] = s[i], a[i] = i, cnt[ c[i] ]++;
    for(int i = 0; i < mx-1; i++) head[i+1] = head[i] + cnt[i];
    for(int k = 0; k < n; k = max(1, k<<1)) {
      for(int i = 0; i < n; i++) {
        int j = (a[i] - k + n) % n;
        a1[ head[ c[j] ]++ ] = j;
      }
      swap(a1, a);
      for(int i = 0, x = a[0], y, col = 0; i < n; i++, x = a[i], y = a[i-1]) {
        c1[x] = (i && c[x] == c[y] && c[x+k] == c[y+k]) ? col : ++col;
        if(!i || c1[x] != c1[y]) head[col] = i;
      }
      swap(c1, c);
      if(c[ a[n-1] ] == n) break;
    }
    swap(sa, a);
    for(int i = 0; i < n; i++) pos[ sa[i] ] = i;
    for(int i = 0, k = 0, j; i < n; lcp[ pos[i++] ] = k) { /// lcp[i, i+1]
      if(pos[i] == n-1) continue;
      for(k = max(0, k-1), j = sa[ pos[i]+1 ]; s[i+k] == s[j+k]; k++);
    }
  }
  int& operator[] ( int i ){ return sa[i]; }
};

int main(){
  ios_base::sync_with_stdio(0), cin.tie(0);
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  string check1,check2;
  cin >> check1 >> check2;

  string send = check1 + "$" + check2;

  suffix_array imp(send);

  vector<int> sa = imp.sa, lcp = imp.lcp;

  segtree seg(lcp.size(),lcp);

  int last1= -1, last2 = -1;
  int ans = 0;
  for(int i = 0; i < sa.size();++i){
    if(sa[i] < check1.size())
      last1 = i;
    else if(sa[i] < send.size() && send[sa[i]] != '$')
      last2 = i;
    if(last1 != -1 && last2 != -1){
      int mi = min(last1,last2), ma = max(last1,last2);
      ans = max(ans,seg.query(mi,ma-1).val);
    }
  }

  cout << ans << "\n";

  return 0;
}