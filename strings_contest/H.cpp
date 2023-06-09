 //I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

struct state {
    int len, link;
    //Cuenta cuantas veces aparecen los strings que correponden a este nodo en el string
    ll cnt = 0;
    //Almacena cuantos strings (diferentes) corresponden a este nodo
    int tam;
    //Indica si este nodo corresponde a sufijos del string original
    bool terminal = false;
    map<char, int> next;
    bool visited = false;
};

const int MAXLEN = 1e5 + 2;
state st[MAXLEN * 2];
int sz, last;


void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

vector<string> vals;
vector<vector<int>> best;

void dfs(int now){
    if(st[now].visited) return;
    if(st[now].link == -1) return;
    dfs(st[now].link);
    for(int j = 1; j < vals.size();++j)
        best[j][now] = max(best[j][now],best[j][st[now].link]);
    st[now].visited = 1;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string temp;
    while(getline(cin,temp)){
        vals.pb(temp);
    }

    sa_init();
    for(auto &let:vals[0]){
        sa_extend(let);
    }

    best.resize(vals.size(),vector<int>(MAXLEN * 2,0));

    for(int i = 1; i < vals.size(); ++i){
        int cur = 0, len = 0;
        for(auto &let:vals[i]){
            while(cur > 0 && !st[cur].next.count(let)){
                cur = st[cur].link;
                len = st[cur].len;
            }
            if(st[cur].next.count(let)) ++len, cur = st[cur].next[let];
            best[i][cur] = max(len,best[i][cur]);
        }

    }

    int ans = 0;
    for(int i = 1; i <= last && vals.size() > 1;++i){
        if(st[i].link != -1)
            dfs(i);
        int temp = INT_MAX;
        for(int j = 1; j < vals.size();++j){
            temp = min(best[j][i],temp);
        }
        ans = max(ans,temp);
    }   


    cout << ans << "\n";
    return 0;
}