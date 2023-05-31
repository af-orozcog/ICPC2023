//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

// Header files, namespaces,
// macros as defined above
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

/// Complexity: O(|N|*log(|N|))
/// Tested: https://tinyurl.com/y8wdubdw
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

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    bool fi = 0;
    int n;
    while(cin >> n && n){
        if(fi) cout << "\n";
        fi = 1;

        vector<string> values(n);
        for(auto &va:values) 
            cin >> va;

        if(n == 1){
            cout << values[0] << "\n";
            continue;
        }

        vector<int> ids;
        string toSend = "";
        char toAdd = 0;
        for(auto &va:values){
            toSend += va;
            ids.pb(toSend.size()-1);
            toSend += toAdd;
            ++toAdd;
            while(toAdd >= 'a' && toAdd <= 'z')
                ++toAdd;
        }

        suffix_array imp(toSend);

        segtree seg(imp.lcp.size(),imp.lcp);

        int top = n / 2 + 1;

        vector<string> ans;

        map<int,int> mp;
        ordered_set mins;

        for(int j = 1; j < imp.sa.size();++j){
            if(toSend[imp.sa[j]] < 'a' || toSend[imp.sa[j]] > 'z'){
                mp.clear();
                mins.clear();
                continue;
            }
            int val = lower_bound(ids.begin(),ids.end(),imp.sa[j]) - ids.begin();
            if(mp.count(val))
                mins.erase(mp[val]);
            mp[val] = j;
            mins.insert(j);
            if(mins.size() >= top){
                int sz = seg.query(*mins.find_by_order(mins.size()-top),j-1).val;
                if(!sz) continue;
                if(!ans.size() || (ans.size() && ans.back().size() == sz))
                    ans.pb(toSend.substr(imp.sa[j],sz));
                else if(ans.size() && ans.back().size() < sz){
                    ans.clear();
                    ans.pb(toSend.substr(imp.sa[j],sz));
                }
            }

        }

        sort(ans.begin(),ans.end());

        for(int i = 0; i < ans.size();++i){
            if(i && ans[i] != ans[i-1])
                cout << ans[i] << "\n";
            else if(!i)
                cout << ans[i] << "\n";
        }

        if(!ans.size())
            cout << "?\n";
    } 

    return 0;
}