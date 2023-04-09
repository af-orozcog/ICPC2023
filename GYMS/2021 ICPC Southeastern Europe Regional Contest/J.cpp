// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)

using namespace std;

typedef pair<int,int> pii;

bool checkPossible(set<pii> &abP, set<pii> &acP){
    auto check = *(abP.begin());
    auto val = acP.lower_bound({check.ff,0});
    return val != acP.end();
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n;
    string see;
    set<int> a,b,c;
    set<pii> ab,bc,ac,abP,bcP,acP;
    cin >> n >> see;

    for(int i = 0; i < 2*n;++i){
        if(see[i] == 'A')
            a.insert(i);
        else if(see[i] == 'B'){
            if(a.size()){
                int val = *(a.begin());
                ab.insert({val,i});
                a.erase(a.begin());
                abP.insert({i,val});
            }
            else if(abP.size() && acP.size() && checkPossible(abP,acP)){
                auto check1 = *(abP.begin());
                auto check2 = *(acP.lower_bound({check1.ff,0}));
                abP.erase(abP.begin());
                acP.erase(check2);
                ab.erase({check1.ss,check1.ff});
                ac.erase({check2.ss,check2.ff});
                bc.insert({check1.ff,check2.ff});
                ab.insert({check2.ss,i});
                abP.insert({i,check2.ss});
                bcP.insert({check2.ff,check1.ff});
                a.insert(check1.ss);
            }
            else 
                b.insert(i);
        }
        else{
            if(b.size()){
                int val = *(b.begin());
                bc.insert({val,i});
                bcP.insert({i,val});
                b.erase(b.begin());
            }
            else if(a.size()){
                int val = *(a.begin());
                ac.insert({val,i});
                acP.insert({i,val});
                a.erase(a.begin());
            }
            else if(ab.size()){
                pii check = *(ab.begin());
                bc.insert({check.ss,i});
                bcP.insert({i,check.ss});
                ab.erase(ab.begin());
                abP.erase({check.ss,check.ff});
                a.insert(check.ff);
            }
        }
    }

    if(ab.size() + ac.size() + bc.size() == n){
        cout << "YES\n";
        for(auto &va:ab){
            cout << va.ff + 1 << " " << va.ss + 1<< "\n"; 
        }
        for(auto &va:ac){
            cout << va.ff + 1 << " " << va.ss + 1<< "\n"; 
        }
        for(auto &va:bc){
            cout << va.ff + 1 << " " << va.ss + 1<< "\n"; 
        }
    }
    else cout << "NO\n";

    return 0;
}

// abcb (a) (b) => (a,b) c => a (b,c) b => (a,b) (b,c)  
//(a,c) (a,b) c b,c a b c 
// (a,c) (a,b) b 
// abacbc => (a,b) (a,c) b => (a,b) (a,c) b b 
