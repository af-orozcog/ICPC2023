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
};

const int MAXLEN = 1e6;
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

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    sa_init();

    string imp; cin >> imp;
    for(auto let:imp)
        sa_extend(let);

    int nm; cin >> nm;

    while(nm--){
        string check; cin >> check;
        int ans = 1;
        int now = 0;
        for(auto let: check){
            if(!st[now].next.count(let)){
                now = 0;
                ++ans;
            }
            if(!st[now].next.count(let)){
                ans = -1;
                break;
            }
            now = st[now].next[let];
        }

        cout << ans << "\n";
    }

    return 0;
}