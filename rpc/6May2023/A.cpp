 //I love Manuela
#include <bits/stdc++.h>
#define ll __int128
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

vector<vector<pii>> posi;

void generate(int x, int y, vector<pii> &now){
    now.pb({x,y});
    if(x == 11 || y == 11){
        posi.pb(now);
        now.pop_back();
        return;
    }
    if((x+y+1) & 1){
        generate(y,x+1,now);
        generate(y+1,x,now);
    }
    else{
        generate(x+1,y,now);
        generate(x,y+1,now);
    }
    now.pop_back();
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
    
    int n;cin >> n;
    vector<pii> values;
    for(int i = 0; i < n;++i){
        string see; cin >> see;
        int where = see.find("-");
        int bef = stoi(see.substr(0,where));
        int af = stoi(see.substr(where+1,see.size()));
        values.pb({bef,af});
    }

    int ma = 0;


    

    int left = n - ma;


    if(left)
        cout << "error "<< see + 1 << "\n";

    else cout << "ok\n";


    return 0;
} 