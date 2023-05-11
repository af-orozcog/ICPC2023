//I love Manuela
#include <bits/stdc++.h>
#define ll __int128
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

ll fastSum(ll n){
    return (n*(n+1))>>1;
}

ll fastSum2(ll n){
    return (((n*(n+1))/2)*(2*n+1))/3;
}

ll mod = 1;

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
    mod <<= 64;
    long long a,b,c,n;
    cin >> a >> b >> c >> n;
    ll ans = 0;

    if(n&1){
        ll imp = n>>1;
        ans += imp*fastSum(imp-1) - fastSum2(imp-1);
        ans <<= 1;
        ans += fastSum(imp);
    } else {
        ll imp = ((n-2)>>1);
        ans += (imp*fastSum(imp-1) - fastSum2(imp-1)) + (imp*(imp-1) - fastSum(imp-1));
        ans <<= 1;
        ans += fastSum(imp)<<1;
        ans += n-2; 
    }

    if(a == b && b == c) ans = ans;
    else if(a == b || b == c || a == c) ans *= 3;
    else ans *= 6;
    
    ans %= mod;

    unsigned long long see = ans; 

    cout << see << "\n";

    return 0;
}