//I love Manuela
#include <bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

int const MAX = 4*(1e5)+2;
int BIT[2][MAX];

void update(int index, int p, int val){
    while(p < MAX){
        BIT[index][p] += val;
        p += (p&(-p));
    }
}

int query(int index, int p){
    int ans = 0;
    while(p){
        ans += BIT[index][p];
        p -= (p&(-p));
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
    int n,m,l; cin >> n >> m >> l;

    vector<pii> fish(n);
    vector<int> values; 
    for(auto &va:fish){
        cin >> va.ff >> va.ss;
        values.pb(va.ss-va.ff);
        values.pb(va.ss+va.ff);
    }
    sort(fish.begin(),fish.end());

    vector<pii> fisher(m);
    for(int i = 0; i < m;++i){
        cin >> fisher[i].ff;
        fisher[i].ss = i;
    }

    sort(values.begin(),values.end());
 
    map<int,int> mp;
    for(int i = 0, j = 0; i < values.size();++i){
        if(!i || values[i] != values[i-1]){
            mp[values[i]] = ++j;
        }
    }

    sort(fisher.begin(),fisher.end());

    vector<int> ans(m,0);

    for(int i = 0, j = 0; i < fisher.size();++i){
        while(j < fish.size() && fish[j].ff < fisher[i].ff){
            //segment tree operation
            update(0,mp[fish[j].ss-fish[j].ff],1);
            ++j;
        }
        auto check = mp.upper_bound(l-fisher[i].ff);
        if(check == mp.begin()) continue;
        --check;
        ans[fisher[i].ss] += query(0,check->ss);
    }

    for(int i = fisher.size()-1, j = fish.size()-1; i > -1; --i){
        while(j > -1 && fish[j].ff >= fisher[i].ff){
            update(1,mp[fish[j].ss+fish[j].ff],1);
            //segment tree operation
            --j;
        }
        auto check = mp.upper_bound(l+fisher[i].ff);
        if(check == mp.begin()) continue;
        --check;
        ans[fisher[i].ss] += query(1,check->ss);
    }

    for(auto va:ans)
        cout << va << "\n";
    return 0;
}