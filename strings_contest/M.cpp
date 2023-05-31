 //I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

vector<vector<int>> bt;

void prepare(string &see){
    bt.resize(see.size(),vector<int>(see.size(),0));
    for(int i = 0; i < see.size();++i){
        int l = i, r = i;
        while(l > -1 && r < see.size() && see[l] == see[r]){
            ++bt[l][r];
            --l,++r; 
        }
        l = i,r = i + 1;
        while(l > -1 && r < see.size() && see[l] == see[r]){
            ++bt[l][r];
            --l,++r; 
        }
    }

    for(int j = 0; j < bt[0].size();++j){
        for(int i = 0; i < bt.size();++i){
            if(i)
                bt[i][j] += bt[i-1][j];
            if(j)
                bt[i][j] += bt[i][j-1];
            if(i && j)
                bt[i][j] -= bt[i-1][j-1];
        }
    }
} 


int query(int l, int r){
    int ans = bt[r][r];
    if(l){
        ans -= bt[r][l-1] + bt[l-1][r];
        ans += bt[l-1][l-1];
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    string see; cin >> see;
    prepare(see);
    int q; cin >> q;
    while(q--){
        int l,r; cin >> l >> r;
        --l,--r;
        cout << query(l,r) << "\n";
    }

    return 0;
}