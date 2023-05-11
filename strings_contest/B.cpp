// I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back

using namespace std;

typedef pair<int,int> pii;

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

bool checkValid(int center, int length, vector<int> &check){
    int leftCenter = center-length;
    if((check[leftCenter*2-1] - 1)/2 >= length)
        return true;
    return false;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

    int t;
    cin >> t;

    while(t--){
        string see; cin >> see;
        vector<int> check = manacher(see);
        int ans = 0;
        for(int i = 1; i < see.size(); ++i){
            if(i*2-1 < check.size() && ((check[i*2-1] - 1)/4)*4 > ans){
                int start = ans + 4;
                int from = (check[i*2-1] - 1);
                while(from %4 != 0) --from;
                while(from >= start && !checkValid(i,from/4,check)) from -= 4;
                ans = max(from,ans);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
//{2, 1, 2, 1, 2, 5, 2, 1, 2, 1, 2}
//{2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 7, 2, 1, 2, 1, 2, 13, 2, 1, 2, 1, 2, 7, 2, 1, 2, 1, 2}