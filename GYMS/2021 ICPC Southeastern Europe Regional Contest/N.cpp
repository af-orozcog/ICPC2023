// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n; cin >> n;
    vector<ll> a(n+1),b(n+1);
    vector<ll> imp(n+1);
    for(auto &va:a) cin >> va;
    for(auto &va:b) cin >> va;

    for(int i = 0; i <= n;++i)
        imp[i] = a[i] - b[i];

    ll ans = 0;

    ll last = 0;
    for(int i = n; i > -1;--i){
        last += imp[i];
        if(last < 0){
            ll check = (abs(last) + (abs(last) % 2))>>1;
            ans += check;
            last = -check; 
        }
        if(last >= 0) last = 0;
    }

    cout << (last < 0? -1: ans) << "\n";
 
    return 0;
}

