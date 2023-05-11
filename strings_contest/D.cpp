// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

typedef pair<int,int> pii;

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return res;
}

ll fastSum(ll n){
    return (n*(n+1))>>1;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
    
    int t; cin >> t;

    while(t--){
        int k; string see;
        cin >> k >> see;
        vector<vector<int>> bad(see.size()+1);
        vector<int> check = manacher(see);
        ll ans = 0;
        for(int i = 0, now = -1; i < check.size()-1;++i){
            if(!(i&1)){
                ++now;
                int imp = ((check[i]-1)>>1);
                
                if(imp*2 < k) continue;
                
                imp = (k + (k % 2))>>1;
                bad[now-imp].pb(now);
                bad[now+imp-1].pb(now);
            }
            else{
                int imp = (check[i]>>1);

                if(imp*2 -1 < k) continue;

                imp = ((k + (k % 2 == 0))>>1) + 1;
                
                bad[now-imp+1].pb(now+see.size());
                bad[now+imp-1].pb(now+see.size());
            }
        }
        map<int,int> mp;
        for(int i = 0, j = 0; j < see.size();++j){
            int notGood = 0;
            for(auto cou:bad[j]){
                if(++mp[cou] == 2) notGood++;
            }
            while(notGood){
                for(auto va:bad[i]){
                    if(mp[va] == 2) --notGood;
                    --mp[va];
                }
                ++i;
            }
            ans += j-i+1;
        }

        cout << ans << "\n";
    }

    return 0;
}