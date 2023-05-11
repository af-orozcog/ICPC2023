//I love Manuela
#include <bits/stdc++.h>
#define ll __int128
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

bool sorted(vector<int> &check){
    bool ans = 1;
    for(int i = 1; i < check.size() && ans;++i){
        ans = (check[i] > check[i-1]);
    }
    return ans;
}

void sortK(vector<int> &check, int k){
    priority_queue<int> q;
    int i = 0;
    for(int j = 0; j < check.size();++j){
        q.push(check[j]);
        if(q.size() == k){
            check[i++] = q.top();
            q.pop();
        }
    }
    while(q.size()){
        check[i++] = q.top();
        q.pop();
    }
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
    
    int n,k; cin >> n >> k;
    vector<int> nums(n);
    for(auto &va: nums) cin >> va;

    int ans = 0;
    do {
        ++ans;
        sortK(nums,k);
    }while(!sorted(nums));

    cout << ans << "\n";

    return 0;
}