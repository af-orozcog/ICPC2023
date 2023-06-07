#include<bits/stdc++.h> 
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;

#define oo INT_MAX

typedef pair<int,int> pii;

template<class T> struct Dinic {
	struct Edge {
		int v, inv; T cap, flow;
		Edge(int v , int inv, T cap, T flow): v(v), inv(inv), cap(cap), flow(flow) {}
	};
	int n, s, t, top;
	vector<int> level,q;
	vector<vector< Edge>> graph;
	Dinic( int n ): n(n), top(0), level(n), q(n + 1), graph(n) {}
	void addEdge(int u, int v, T cap){
		graph[u].pb(Edge(v, graph[v].size(), cap, 0));
		graph[v].pb(Edge(u, graph[u].size() - 1, 0, cap));
	}
	bool bfs() {
		fill(level.begin(), level.end(), -1);
		q[++top] = s;
		level[s] = 0;
		while(top) {
			int u = q[top]; top--;
			for(int i = 0; i < (int)graph[u].size();++i){
				Edge &e = graph[u][i];
				if(e.cap > 0 && level[e.v] == -1){
					level[e.v] = level[u] + 1;
					q[++top] = e.v;
				}
			}
		}
		return level[t] != -1;
	}

	T dfs(int u, T pushed) {
		if (u == t) return pushed;
		T ans = 0;
		for(int i = 0; i < (int)graph[u].size(); ++i){
			Edge &e = graph[u][i];
			if(e.cap > 0 && level[e.v] == level[u] + 1){
				T newflow = dfs(e.v, min(pushed,e.cap));
				ans += newflow;
				pushed -= newflow;
				e.cap -= newflow, e.flow += newflow;
				graph[e.v][e.inv].cap += newflow;
				graph[e.v][e.inv].flow -= newflow;
				if(pushed == 0) return ans;
			}
		}
		if(!ans) level[u] = -1;
		return ans;
	}
	T maxflow(int u, int v) {
		T ans = 0; s = u, t = v;
		while(bfs()) ans += dfs(s, oo);
		return ans;
	}
};

int main(){
	ios_base::sync_with_stdio(0),cin.tie(0);
	int t; cin >> t;

	while(t--){
		int n; cin >> n;
		unordered_map<int,int> row,col;
		vector<pii> vals(n);

		for(auto &va: vals) {
			cin >> va.ff >> va.ss;
			if(!row.count(va.ff))
				row[va.ff] = row.size();
			if(!col.count(va.ss))
				col[va.ss] = col.size();
		}

		int toAdd = row.size()+1;

		Dinic<ll> dn(row.size()+col.size()+2);

		for(auto &va: vals){
			dn.addEdge(row[va.ff]+1, col[va.ss]+toAdd,1);
		}

		for(auto val: row)
			dn.addEdge(0,val.ss+1,1);

		for(auto val: col)
			dn.addEdge(val.ss+toAdd,row.size()+col.size()+1,1);

		cout << dn.maxflow(0,row.size()+col.size()+1) << endl;

	}

	return 0;
}