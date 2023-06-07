#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>

using namespace std;

const int oo = 1e9;
template <class T> struct Dinic {
	struct Edge {
		int v, inv; T cap, flow;
		Edge(int v, int inv, T cap, T flow) : v(v), inv(inv), cap(cap), flow(flow) {}
	};
	int n, s, t;
	vector <int> level;
	vector < vector <Edge> > graph;
	Dinic(int n) : n(n), level(n), graph(n) {}
	void addedge(int u, int v, T cap) {
		graph[u].push_back(Edge(v, graph[v].size(), cap, 0));
		graph[v].push_back(Edge(u, graph[u].size() - 1, 0, cap));
	}
	bool bfs() {
		fill(level.begin(), level.end(), -1);
		queue <int> q;
		q.push(s);
		level[s] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for(int i = 0; i < graph[u].size(); ++i) {
				Edge &e = graph[u][i];
				if(e.cap > 0 && level[e.v] == -1) {
					level[e.v] = level[u] + 1;
					q.push(e.v);
				}
			}
		}
		return level[t] != -1;
	}
	T dfs(int u, T pushed) {
		if(u == t) return pushed;
		T ans = 0;
		for(int i = 0; i < graph[u].size(); ++i) {
			Edge &e = graph[u][i];
			if(e.cap > 0 && level[e.v] == level[u] + 1) {
				T newflow = dfs(e.v, min(pushed, e.cap));
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
const int maxn=  510;
int col[maxn];
vector <int> graph[maxn];
bool check(string& s, string& t) {
	int n = s.size();
	vector <int> d;
	for (int i = 0; i < n; i++) if (s[i] != t[i]) d.push_back(i);
	if (d.size() != 2) return 0;
	return s[d[0]] == t[d[1]] && s[d[1]] == t[d[0]];
}
void dfs(int u) {
	for(int& v : graph[u]) {
		if (col[v] != -1) continue;
		col[v] = 1 - col[u];
		dfs(v);
	}
}
int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	int n; cin >> n;
	vector <string> a(n);
	for (int i = 0; i < n;i++) cin >> a[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (check(a[i], a[j])) {
				graph[i].push_back(j);
				//cout << a[i] << ' ' << a[j] << endl;
				//cout << i << ' ' << j << endl;
			}
		}
	}
	for (int i = 0; i < n; i++) col[i] = -1;
	for (int i = 0; i < n; i++) {
		if (col[i] != -1)  continue;
		col[i] = 0;
		dfs(i);
	}
	Dinic <int> net(n + 2);
	int s = n, t = n + 1;
	for (int i = 0; i < n; i++) {
		if (col[i]) net.addedge(i, t, 1);
		else {
			net.addedge(s, i, 1);
			for (int& v : graph[i]) net.addedge(i, v, 1);
		}
	}
	//int ans = net.maxflow(s,t);
	cout << n - net.maxflow(s, t) << endl;
	return 0;
}
