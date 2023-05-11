// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back

using namespace std;

typedef pair<int,int> pii;

vector<int> pi_function(string &s){
    int n = (int)s.length();
	vector<int> pi(n);
	for(int i =1; i<n; i++){
		int j = pi[i-1];
		while(j>0&&s[i]!=s[j])
			j=pi[j-1];
		if(s[i]==s[j])
			j++;
		pi[i]=j;
	}
	return pi;
}


int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    string s;
    cin >> s;

    vector<int> imp(s.size()+2);
    vector<int> pi = pi_function(s);
    for(auto va:pi)
        ++imp[va];

    
    for(int i = s.size(); i > 0;--i){
        imp[pi[i-1]] += imp[i];
    }

    for(int i = 1; i <= s.size();++i)
        ++imp[i];

    vector<pii> answer;

    int now = pi.back();
    while(now){
        answer.pb({now,imp[now]});
        now = pi[now-1];
    }
    reverse(answer.begin(),answer.end());

    answer.pb({s.size(),1});

    cout << answer.size() << "\n";

    for(auto va:answer)
        cout << va.ff << " " << va.ss << "\n";

    
    return 0;
}