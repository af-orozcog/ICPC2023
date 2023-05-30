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

#ifdef DBP
#define deb(...) fprintf(stderr,__VA_ARGS__)
#else
#define deb(...) 0
#endif
#define fst first
#define snd second
#define fore(x,a,b) for(int x=(a), qwerty=(b); x<qwerty; x++)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;

/* *
 *
 * Too many mind, no mind.
 *
 * */
typedef long double td; typedef vector<int> vi; typedef vector<td> vd;
const td INF=0;//for maximum set INF to 0, and negate costs
bool zero(td x){return fabs(x)<1e-9;}//change to x==0, for ints/ll
struct Hungarian{
    int n; vector<vd> cs; vi L, R;
    Hungarian(int N, int M):n(max(N,M)),cs(n,vd(n)),L(n),R(n){
        fore(x,0,N)fore(y,0,M)cs[x][y]=INF;
    }
    void set(int x,int y,td c){cs[x][y]=c;}
	td assign() {
		int mat = 0; vd ds(n), u(n), v(n); vi dad(n), sn(n);
		fore(i,0,n)u[i]=*min_element(ALL(cs[i]));
		fore(j,0,n){v[j]=cs[0][j]-u[0];fore(i,1,n)v[j]=min(v[j],cs[i][j]-u[i]);}
		L=R=vi(n, -1);
		fore(i,0,n)fore(j,0,n)
			if(R[j]==-1&&zero(cs[i][j]-u[i]-v[j])){L[i]=j;R[j]=i;mat++;break;}
		for(;mat<n;mat++){
		    int s=0, j=0, i;
		    while(L[s] != -1)s++;
		    fill(ALL(dad),-1);fill(ALL(sn),0);
		    fore(k,0,n)ds[k]=cs[s][k]-u[s]-v[k];
		    for(;;){
		        j = -1;
		        fore(k,0,n)if(!sn[k]&&(j==-1||ds[k]<ds[j]))j=k;
		        sn[j] = 1; i = R[j];
		        if(i == -1) break;
		        fore(k,0,n)if(!sn[k]){
		            auto new_ds=ds[j]+cs[i][k]-u[i]-v[k];
		            if(ds[k] > new_ds){ds[k]=new_ds;dad[k]=j;}
		        }
		    }
		    fore(k,0,n)if(k!=j&&sn[k]){auto w=ds[k]-ds[j];v[k]+=w,u[R[k]]-=w;}
		    u[s] += ds[j];
		    while(dad[j]>=0){int d = dad[j];R[j]=R[d];L[R[j]]=j;j=d;}
		    R[j]=s;L[s]=j;
		}
		td value=0;fore(i,0,n)value+=cs[i][L[i]];
		return value;
	}
};
const int maxn = 2e7 + 20, maxm = 1010;
int n;
bool sieve[maxn];
int a[maxm];
int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	sieve[0] = sieve[1] = 1;
	for (int i = 0; i < maxn; i++) {
		if (sieve[i]) continue;
		for (int j = i + i; j < maxn; j += i) sieve[j] = 1;
	}
	scanf("%d ",&n);
	int cnt = 0;
	for (int i=0; i < n; i++) {
		scanf("%d ", &a[i]);
		if (a[i] == 1) cnt++;
	}


	int one = -1;
	for (int i = 0; i < n; i++) {
		if (a[i] == 1) {
			one = i;
			break;
		}
	}

	Hungarian net(n+10, n+10);

	for (int i = 0; i < n; i++) {
		if (a[i]&1) continue;

		for (int j= 0; j < n; j++) {
			if (a[j] == 1) continue;
			if (!sieve[a[i] + a[j]]) net.set(i, j, 0);
		}
		if (one != -1 && !sieve[a[i] + a[one]]) net.set(i, one, 0);
	}

	int total = n - cnt + (one != -1);
	int ans = total - net.assign();

	printf("%d\n",ans);
	return 0;
}

