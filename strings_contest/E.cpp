// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

//funcion para calcular la z function de un string
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
        string see,word; int k;
        cin >> see >> word >> k;
        string imp = word + "#" + see;
        auto kmp1 = z_function(imp);
        reverse(word.begin(),word.end());
        reverse(see.begin(),see.end());
        imp = word + "#" + see;
        auto kmp2 = z_function(imp);
        kmp1.erase(kmp1.begin(),kmp1.begin()+word.size()+1);
        kmp2.erase(kmp2.begin(),kmp2.begin()+word.size()+1);
        reverse(kmp2.begin(),kmp2.end());
        int ans = 0;

        if(k == word.size()){
            cout << (int)see.size() - k + 1 << "\n";
            continue;
        }

        for(int i = 0; i + word.size() <= see.size();++i){
            if(kmp1[i] + kmp2[i+word.size()-1] + k >= word.size()) ++ans;
        }

        cout << ans << "\n";
    }

    return 0;
}
//"romeo#oxwmeorozkowhereforeartthouromeo"
//"oemor#oemoruohttraeroferehwokzoroemwxo"
//{0, 0, 0, 1, 0, 0, 1, 2, 3, 4, 5, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 2, 3, 0, 0, 1}