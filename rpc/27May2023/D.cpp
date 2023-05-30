//I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n,q; cin >> n >> q;

	vector<int> nums(n);
	for(auto &va:nums) cin >> va;

	sort(nums.begin(),nums.end());

	while(q--){
		int op; cin >> op;
		if(op == 2){
			int a,b; cin >> a >> b;
			auto low = lower_bound(nums.begin(),nums.end(),a);
			auto up = upper_bound(nums.begin(),nums.end(),b);
			cout << distance(low,up) << "\n";
		}else{
			int a; cin >> a;
			if(nums.back() < a) nums.pb(a);
			else{
				int pos = lower_bound(nums.begin(),nums.end(),a) - nums.begin();
				if(nums[pos] != a)
					nums[pos] = a;
			}
		}
	}

	return 0;
}