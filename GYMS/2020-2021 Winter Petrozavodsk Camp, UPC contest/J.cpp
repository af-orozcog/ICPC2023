//I love Manuela
#include <bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;


int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    unordered_set<string> imp;

    const ll top = 1e9;

    for(ll i = 1; i*i <= top;++i){
        if((i*i) % 100 == 25)
            imp.insert(to_string(i*i));
    }

    int t; cin >> t;
    while(t--){
        ll k; cin >> k;
        int add = 0;
        ll temp = k;
        for(ll i = 2; i*i <= k && temp != 1;++i){
            if(temp % i == 0){
                add += imp.count(to_string(i) + "25");
            }
            while(temp % i == 0){
                temp /= i;
            }
        }
        if(temp != 1){
            add += imp.count(to_string(temp) + "25");
        }
        cout << add + 1 << "\n";
    }

    return 0;
}