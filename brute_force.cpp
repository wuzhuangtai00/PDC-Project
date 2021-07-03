#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<vector>
#define pb push_back
#define mk make_pair
typedef pair<int,int> pin;
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;


inline void read(int &x){
    char ch = getchar();
    while(ch == '%') {
        while(ch != '\n') ch = getchar();
        ch = getchar();
    }
	x=0;int f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}

int n, m;

const ld eps = 1e-5;
const int maxn = 12000;
double a[maxn][maxn];
set<pin> pos;

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        a[x][y] = z;
		a[y][x] = z;
		pos.insert(mk(x, y));
    }
}


double l[maxn][maxn];

struct data{
	int x, y;
	double v;
	data(int _x, int _y, double _z) {
		 x = _x; y = _y; z = _z;
	}
};

vector<data> L, U;

inline void solve() {
	rep(i, 1, n) {
		rep(k, i, n) {
			if(a[i][k] != 0) {
				U.pb(data(i, k, a[i][k]));
			}			
		}
		L.pb(data(i, i, 1));
		rep(j, i + 1, n) {
			if (a[j][i] == 0) continue;
			double d = a[j][i] / a[i][i];
			L.pb(data(j, i, d));
			rep(k, i, n) a[j][k] -= d * a[i][k];
		}
	}
}

double Lm[maxn][maxn], Um[maxn][maxn];
set<int> Ls[maxn], Ul[maxn];

inline void check_ans() {
	for(unsigned i = 0; i < L.size(); i++) {
		data x = L[i];
		Lm[x.x][x.y] = x.z;
		Ls[x.y].insert(x.x);
	}

	for(unsigned i = 0; i < U.size(); i++) {
		data x = U[i];
		Um[x.x][x.y] = x.z;
		Ul[x.x].insert(x.y);
	}
	rep(j, 1, n) {
		for(int i: Ls[y]) for(int k: Ul[y]) {
			a[i][k] -= Lm[i][j] * Um[j][k];
		}
	}
	bool flag = 1;
	for(pin w: pos) {
		if(fabs(a[w.w1][w.w2]) > eps) flag = 0;
	}
	printf("%d\n", flag);
}

inline void output() {
	printf("%d\n", L.size());
	for(unsigned i = 0; i < L.size(); i++) {
		data x = L[i];
		printf("%d %d %d\n", x.x, x.y, x.z);
	}

	puts("");
	printf("%d\n", U.size());
	for(unsigned i = 0; i < U.size(); i++) {
		data x = U[i];
		printf("%d %d %d\n", x.x, x.y, x.z);
	}
}

int main() {
    init();

    solve();

	check_ans();

	output();
}