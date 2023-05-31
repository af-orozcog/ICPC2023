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

int contar(int v){
    if(st[v].cnt){
        return st[v].cnt;
    }
    if(v) {
        st[v].tam = st[v].len - st[st[v].link].len;
    }
    int rta = st[v].terminal;
    for (auto const& x : st[v].next){
        rta+=contar(x.second);
    }
    return st[v].cnt = rta;
}

void asignar_terminales() {
    int est = last;
    while(est>0){
        st[est].terminal = true;
        est = st[est].link;
    }
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    int tt; cin >> tt;
    while(tt--){
        for(int i = 0; i <= last;++i){
            st[i].next.clear();
            st[i].terminal = 0;
            st[i].cnt = 0;
        }
        string check; cin>> check;
        
        sa_init();

        for(auto let:check)
            sa_extend(let);

        asignar_terminales();
        contar(0);
        int ans = 0;

        for(int i = 0; i <= last;++i){
            if(st[i].cnt > 1)
                ans = max(ans,st[i].len);
        }

        cout << ans << "\n";

    }

    return 0;
}
