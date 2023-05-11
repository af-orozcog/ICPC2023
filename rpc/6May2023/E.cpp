 //I love Manuela
#include <bits/stdc++.h>
#define ll __int128
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

vector<vector<int>> g;

int minCycle(int from){
    queue<int> q;
    q.push(from);
    vector<int> dist(g.size(),-1);
    vector<int> dadIs(g.size(),-1);
    dist[from] = 0;
    dadIs[from] = -1;
    int ans = INT_MAX;
    while(q.size()){
        int dad = q.front();
        q.pop();
        if(ans != INT_MAX) continue;
        for(auto adj:g[dad]){
            if(dist[adj] == -1){
                dist[adj] = dist[dad] + 1;
                q.push(adj);
                dadIs[adj] = dad;
            }
            else if(adj != dadIs[dad]){
                ans = dist[dad] + dist[adj] + 1;
            }
        }
    }
    return ans;
}

int foundCyclesOdd(int from, int size){
    size >>= 1;
    queue<int> q;
    q.push(from);
    vector<int> dist(g.size(),-1);
    dist[from] = 0;
    int ans = 0;
    while(q.size()){
        int dad = q.front();
        q.pop();
        if(dist[dad] == size) continue;
        for(auto adj:g[dad]){
            if(dist[adj] == -1){
                dist[adj] = dist[dad] + 1;
                q.push(adj);
            }
        }
    }
    for(int i = 0; i < dist.size();++i){
        if(dist[i] == size){
            for(auto adj:g[i]){
                if(dist[adj] == size) ++ans;
            }
        }
    }
    return ans >> 1;
}

int foundCyclesEven(int from, int size){
    size >>= 1;
    queue<int> q;
    q.push(from);
    vector<int> dist(g.size(),-1);
    vector<int> ways(g.size(),0);
    dist[from] = 0;
    ways[from] = 1;
    while(q.size()){
        int dad = q.front();
        q.pop();
        if(dist[dad] == size) continue;
        for(auto adj:g[dad]){
            if(dist[adj] == -1){
                dist[adj] = dist[dad] + 1;
                q.push(adj);
                ways[adj] = ways[dad];
            }
            else if(dist[adj] == dist[dad] + 1)
                ways[adj] += ways[dad];
        }
    }
    int ans = 0;
    for(int i = 0; i < dist.size();++i){
        if(dist[i] == size){
            ans += ways[i]*(ways[i]-1);
        }
    }
    return ans >> 1;
}

int foundCycles(int from, int size){
    if(size&1){
        return foundCyclesOdd(from,size);
    }
    return foundCyclesEven(from,size);
}


int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int n,m; cin >> n >> m;
    g.resize(n);

    for(int i = 0; i < m;++i){
        int a,b; cin >> a >> b;
        --a,--b;
        g[a].pb(b);
        g[b].pb(a);
    }

    int smallest = INT_MAX;

    for(int i = 0; i < n;++i)
        smallest = min(smallest,minCycle(i));

    if(smallest == INT_MAX){
        cout << "0\n";
        return 0;
    }

    int ans = 0;

    for(int i = 0; i < n;++i)
        ans += foundCycles(i,smallest);

    cout << ans / smallest << "\n";

    return 0;
}