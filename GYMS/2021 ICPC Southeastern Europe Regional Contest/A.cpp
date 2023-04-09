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
    int n;
    string a,b;
    cin >> n >> a >> b;
    ll ans = 0;

    for(int i = 0, j = 0; j < n;){
        while(j < n && a[j] == b[j]) ++j;
        if(j < n && a[j] < b[j]){
            //cout << j << " " << i << "\n";
            ll bef = (j-i+1);
            ll af = (n-j);
            //cout << af << " " << bef << "\n";
            ans += bef * af;
            j = j + 1;
            i = j;
        }
        else{
            i = j+1;
            j = j+1;
        }
    }

    cout << ans << "\n";
    return 0;
}