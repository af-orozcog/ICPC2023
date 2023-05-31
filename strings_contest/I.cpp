 //I love Manuela
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
#define EPS 1e-6


// MAXN must be power of 2 !!
const int MAXN=1<<19;
// FFT
struct CD {
    double r,i;
    CD(double r=0, double i=0):r(r),i(i){}
    double real()const{return r;}
    void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){
    return CD(a.r*b.r - a.i*b.i,a.r*b.i + a.i*b.r);}
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const double pi=acos(-1.0);

//Este poly se puede contruir como un array normal
typedef vector<CD> poly;

CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
    for(int i = 0; i<n; ++i)if(R[i]<i)swap(a[R[i]],a[i]);
    for(int m=2; m<=n; m<<=1){
        double z=2*pi/m*(inv?-1:1);
        CD wi=CD(cos(z),sin(z));
        for(int j=0; j<n; j+=m){
            CD w(1);
            for(int k=j, k2=j+(m>>1); k2<j+m; ++k, ++k2){
                CD u=a[k], v=a[k2]*w;
                a[k]=u+v; a[k2]=u-v;
                w=w*wi;
            }
        }
    }
    if(inv)for(int i = 0; i<n; ++i)a[i]/=n;
}
vector<double> multiply(poly& p1, poly& p2){
    int n=p1.size()+p2.size()+1;
    int m=1,cnt=0;
    while(m<=n)m<<=1, ++cnt;
    for(int i = 0; i<m; ++i){
        R[i]=0;
        for(int j = 0; j<cnt; ++j) R[i]=(R[i]<<1)|((i>>j)&1);
    }
    for(int i = 0; i<m; ++i) cp1[i]=0,cp2[i]=0;
    for(int i = 0; i<p1.size(); ++i) cp1[i]=p1[i];
    for(int i = 0; i<p2.size(); ++i) cp2[i]=p2[i];
    dft(cp1,m,false); dft(cp2,m,false);
    for(int i = 0; i<m; ++i) cp1[i] = cp1[i]*cp2[i];
    dft(cp1,m,true);
    n-=2;
    vector<double> res;
    for(int i = 0; i<n; ++i)res.pb(cp1[i].real()); // FFT
    return res;
}

//vector que retorna las posiciones donde hace match el patron p en el string s
//ambos son vectores de letras minusculas. Se debe cambiar el metodo de multiply para que los vectores
//de entrada sean de cd. p puede tener wildcards, corresponde al char en WC.
vector<int> find_pattern(string s, string p){
    char WC = '?';
    int n = s.size(), m = p.size();
    vector<CD> a(n), b(m);
    double alpha;
    int k, wcs =0;
    for(int i =0; i<n; ++i){
        alpha = (2.0*pi*(s[i]-'a'))/26.0;
        a[i].r = cos(alpha), a[i].i=sin(alpha);
    }
    for(int i =0; i<m; ++i){
        if(p[m-i-1]==WC){
            k=0;
            ++wcs;
        }
        else{
            k=1;
        }
        alpha = (2.0*pi*(p[m-i-1]-'a'))/26.0;
        b[i].r = cos(alpha)*k, b[i].i=-sin(alpha)*k;
    }
    vector<double> c = multiply(a,b);
    vector<int> rta;
    wcs = m-wcs;
    for(int i =m-1;  i<n; i++){
        double x = c[i];
        double diff = x-wcs;
        if(abs(diff)<EPS){
            rta.pb(i-(m-1)+1);
        }

    }
    return rta;
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    string fi,se;
    while(cin >> fi >> se){
        cout << find_pattern(fi,se).size() << "\n";
    }

    return 0;
}