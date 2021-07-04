#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<vector>
#include<set>
#include<cmath>
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
#define pb push_back
#define mk make_pair
#define w1 first
#define w2 second

typedef pair<int,int> pin;

inline void read(int &x){
    char ch = getchar();
    while(ch == '%') {
        while(ch != '\n') ch = getchar();
        ch = getchar();
    }
	x=0;int f=1;
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	x*=f;
}

int n, m;

const double eps = 1e-5;
const int maxn = 85000;
double a[maxn][maxn];
double pra[maxn][maxn];
set<pin> pos;

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        a[x][y] = z;
		a[y][x] = z;
		// pos.insert(mk(x, y));
    }
}



struct data{
	int x, y;
	double v;
	data(int _x, int _y, double _z) {
		 x = _x; y = _y; v = _z;
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
		if(a[i][i] == 0) continue;
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
}
FILE *u, *l;

inline void output() {
	fprintf(l, "%d\n", n);
	for(unsigned i = 0; i < L.size(); i++) {
		data x = L[i];
		fprintf(l, "%d %d %.20lf\n", x.x, x.y, x.v);
	}

	// puts("");
	fprintf(u, "%d\n", n);
	for(unsigned i = 0; i < U.size(); i++) {
		data x = U[i];
		fprintf(u, "%d %d %.20lf\n", x.x, x.y, x.v);
	}
}

int main(int argc, char** argv) {
	clock_t pre = clock();
	freopen(argv[1], "r", stdin);
	l = fopen(argv[2], "w");
	u = fopen(argv[3], "w");

    init();

	printf("Init: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

    solve();

	printf("Solve: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

	// check_ans();

	pre = clock();

	output();
	printf("Check Ans: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
}