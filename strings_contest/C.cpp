// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long

using namespace std;

typedef pair<int,int> pii;

vector<int> z_function(string s){
	int n = (int) s.length();
	vector<int> z(n);
	for(int i=1,l=0,r=0; i<n; i++){
		if(i<=r)
			z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n && s[z[i]]==s[i+z[i]])
			++z[i];
		if(i+z[i]-1>r)
			l=i,r=i+z[i]-1;
	}
	return z;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    int t; cin >> t;

    while(t--){
        string see; int times;
        cin >> see >> times;
        if(times == 1)
            cout << see.size() << "\n";
        else{
            vector<int> z = z_function(see);
            int imp = see.size();
            for(int i = 1; i < z.size();++i){
                if(z[i] == (int)see.size()-i){
                    imp = i;
                    break;
                }
            }
            ll ans = (ll)see.size() + ((ll)imp * ((ll)times-1));
            cout << ans << "\n"; 
        }
    }

    return 0;
}