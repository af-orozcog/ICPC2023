// I love Manuela
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;


int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	string a, s; cin >> a >> s;
	set <string> ans;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		for(char& c : a) {
			string cur = i ? s.substr(0, i) : "";
			cur += c;
			cur += s.substr(i);
			ans.insert(cur);

			cur = s;
			cur += c;
			ans.insert(cur);

			cur = s;
			cur[i] = c;
			ans.insert(cur);
		}
		
		string l = i ? s.substr(0, i) : "";
		string r = i + 1 < n ? s.substr(i + 1) : "";
		ans.insert(l + r);
	}
	if(ans.count(s)) ans.erase(s);
	for(auto& i : ans) cout << i << endl;


	return 0;
}