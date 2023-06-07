// I love Manuela
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;

typedef pair<int,int> pii;

int r,c;
vector<vector<char>> matrix;
vector<int> UF;
vector<int> sz;
vector<vector<bool>> marked;
int components;

int movesX[] = {1,-1,0,0};
int movesY[] = {0,0,1,-1};

int movesXS[] = {1,1,-1,-1};
int movesYS[] = {1,-1,1,-1};

int checkXS[][] = {{0,1},{0,1},{0,-1},{0,-1}};
int checkYS[][] = {{1,0},{-1,0},{1,0},{-1,0}};

char checkLet[] = {'/','\\','\\','/'};

int find(int x){
	return UF[x] = (x == UF[x] ? x: find(UF[x]));
}

bool connected(int x, int y){
	return find(x) == find(y);
}

void merge(int x, int y, int flag = 1){
	x = find(x), y = find(y);
	if(x != y){
		if(sz[x] < sz[y]) swap(x,y);
		sz[x] += sz[y];
		UF[y] = x;
		if(flag) --components;
	}
}

int translate(int x, int y){
	return x*c + y;
}

pii revTranslate(int x){
	return {x/c, x%c};
}

void mark(int fromX, fromY){
	++components;
	queue<pii> q;
	q.push({fromX,fromY});
	marked[fromX][fromY] = 1;
	while(q.size()){
		pii dad = q.front();
		q.pop();
		for(int i = 0; i < 4;++i){
			int neX = dad.ff + movesX[i], neY = dad.ss + movesY[i];
			if(neX < 0 || neX >= r || neY < 0 || neY >= c) continue;
			if(matrix[neX][neY] != '.' || marked[neX][neY]) continue;
			q.push({neX,neY});
			marked[neX][neY] = 1;
			merge(translate(dad.ff,dad.ss),translate(neX,neY),0);
		}

		for(int i = 0; i < 4;++i){
			int neX = dad.ff + movesXS[i], neY = dad.ss + movesYS[i];
			if(neX < 0 || neX >= r || neY < 0 || neY >= c) continue;
			if(matrix[neX][neY] != '.' || marked[neX][neY]) continue;
			int bad = 0;
			for(int j = 0; j < 2;++j){
				int checkX = dad.ff + checkXS[i][j], checkY = dad.ss + checkYS[i][j];
				if(checkX < 0 || checkX >= r || checkY < 0 || checkY >= c) continue;
				posi += !(checkLet != matrix[checkX][checkY]); 
			}
			if(posi != 2) continue;
			q.push({neX,neY});
			marked[neX][neY] = 1;
			merge(translate(dad.ff,dad.ss),translate(neX,neY),0);
		}

	}
}

int calcAnswer(){
	int ans = 0;
	vector<vector<int>> dist(r,vector<int>(c,-1));
	queue<pii> q;
	for(int i = 0; i < r;++i){
		for(int j = 0; j < c;++j){
			if(matrix[i][j] == '.'){
				q.push({i,j});
				dist[i][j] = 0;
			}
		}
	}


	while(q.size() && components > 1){
		pii dad = q.front();
		q.pop();
		for(int i = 0; i < 4;++i){
			int neX = dad.ff + movesX[i], neY = dad.ss + movesY[i];
			if(neX < 0 || neX >= r || neY < 0 || neY >= c) continue;
			if(dist[neX][neY] != -1) {
				if(!connected(translate(dad.ff,dad.ss),translate(neX,neY))){
					ans += dist[dad.ff][dad.ss] + dist[neX][neY] + 1;
					merge(translate(dad.ff,dad.ss),translate(neX,neY));
				}
			}
			if(connected(translate(dad.ff,dad.ss),translate(neX,neY))) continue;
			q.push({neX,neY});
			dist[neX][neY] = dist[dad.ff][dad.ss] + 1;
			merge(translate(dad.ff,dad.ss),translate(neX,neY),0);
		}

		for(int i = 0; i < 4;++i){
			int neX = dad.ff + movesXS[i], neY = dad.ss + movesYS[i];
			if(neX < 0 || neX >= r || neY < 0 || neY >= c) continue;
			if(matrix[neX][neY] != '.' ) continue;
			if(dist[neX][neY] != -1){
				if(!connected(translate(dad.ff,dad.ss),translate(neX,neY))){
					ans += dist[dad.ff][dad.ss] + dist[neX][neY] + 1;
					merge(translate(dad.ff,dad.ss),translate(neX,neY));
				}
			}
			if(connected(translate(dad.ff,dad.ss),translate(neX,neY))) continue;
			int bad = 0;
			for(int j = 0; j < 2;++j){
				int checkX = dad.ff + checkXS[i][j], checkY = dad.ss + checkYS[i][j];
				if(checkX < 0 || checkX >= r || checkY < 0 || checkY >= c) continue;
				posi += !(checkLet != matrix[checkX][checkY]); 
			}
			if(posi != 2) continue;
			q.push({neX,neY});
			dist[neX][neY] = dist[dad.ff][dad.ss] + 1;
			merge(translate(dad.ff,dad.ss),translate(neX,neY),0);
		}

	}

	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> r >> c;

	matrix.resize(r,vector<char>(c));
	marked.resize(r,vector<bool>(c,false));
	UF.resize(r*c);
	sz.resize(r*c);

	for(int i = 0; i < UF.size();++i)
		UF[i] = i;

	for(auto &row:matrix){
		for(auto &col:row)
			cin >> col;
	}

	for(int i = 0; i < r;++i){
		for(int  j = 0; j < c;++j){
			if(matrix[i][j] == '.' && !marked[i][j])
				mark(i,j);
		}
	}



	cout << calcAnswer() << "\n";


	return 0;
}