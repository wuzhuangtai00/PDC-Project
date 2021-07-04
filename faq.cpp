#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<vector>
#include<set>
#include<cmath>
#include<sys/time.h>
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
#define pb push_back
#define mk make_pair
#define w1 first
#define w2 second

typedef pair<int,int> pin;


FILE* l,* u;
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
const int maxn = 86000;
double a[maxn][maxn];
vector<int> pos[maxn];

namespace unions{
    int fa[maxn];
    inline void init(int n){
        rep(i, 1, n) fa[i] = i;
    }
    inline int find(int x) {
        if (fa[x] == x) return x;
        int f = find(fa[x]);
        fa[x] = f; return f;
    }
    inline void setfa(int x, int y) {
        fa[find(x)] = find(y);
    }
}

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
		if(fabs(z) < eps) continue;
        a[x][y] = z;
		a[y][x] = z;
        if(x < y) swap(x, y);
		pos[x].pb(y);
    }
	unions::init(n);
}
int cur[maxn], parent[maxn], nmsl[maxn], par[maxn];
double val[maxn];

struct timeval starts, endsss;

struct timeval starts1, endsss1;

inline void solve() {
	fprintf(l, "%d\n", n);
	fprintf(u, "%d\n", n);

    rep(i, 1, n) {
        for(auto x: pos[i]) {
            int w = unions::find(x);
            if(w == i) continue;
            parent[w] = i;
            unions::setfa(w, i);
        }
    }

	gettimeofday(&endsss, NULL);

	double delta = ((endsss.tv_sec  - starts.tv_sec) * 1000000u + 
    	     endsss.tv_usec - starts.tv_usec) / 1.e6;
	printf("Pre: %.4f\n", delta);

	double delta_1 = 0;

	rep(i, 1, n) {
		int cnt = 0, x = i;
		while(x) {
			cur[++cnt] = x;
			x = parent[x];
		}int cnm = 0;
		rep(p, 1, cnt) {
			int j = cur[p];
			if (fabs(a[i][j])>1e-3){
				// fprintf(u, "%d %d %.15lf\n", i, j, a[i][j]);
				nmsl[++cnm] = j;
				val[cnm] = a[i][j];
			}
		}
		// fprintf(l, "%d %d %.12f\n", i, i, 1.0);
		if(fabs(a[i][i]) < eps) continue;
		if(a[i][i] == 0) continue;
		int hr = 0;
		rep(p, 2, cnt) if(fabs(a[cur[p]][i])>=1e-3) par[++hr] = cur[p];

		gettimeofday(&starts1, NULL);

		#pragma omp parallel for num_threads(12) schedule(static)
		rep(p, 1, hr) {
			int k = par[p];
			double d = a[k][i] / a[i][i];
			// fprintf(l, "%d %d %.15lf\n", k, i, d);
			rep(t, 1, cnm){
				int j = nmsl[t];
				a[k][j] -= val[t] * d;
			}	
		}
		
		gettimeofday(&endsss1, NULL);

		delta_1 += ((endsss1.tv_sec  - starts1.tv_sec) * 1000000u + 
    	     endsss1.tv_usec - starts1.tv_usec) / 1.e6;

	}

	printf("Block1: %.4f\n", delta_1);
}
int main(int argc, char** argv) {
	gettimeofday(&starts, NULL);
	puts(argv[0]);
	freopen(argv[1], "r", stdin);
	l = fopen(argv[2], "w");
	u = fopen(argv[3], "w");

    init();

	gettimeofday(&endsss, NULL);

	double delta = ((endsss.tv_sec  - starts.tv_sec) * 1000000u + 
    	     endsss.tv_usec - starts.tv_usec) / 1.e6;

	printf("Init: %.4f\n", delta);

	gettimeofday(&starts, NULL);

    solve();

	gettimeofday(&endsss, NULL);

	 delta = ((endsss.tv_sec  - starts.tv_sec) * 1000000u + 
    	     endsss.tv_usec - starts.tv_usec) / 1.e6;
	printf("Solve: %.4f\n", delta);

	// fclose(l);
	// fclose(u);
	// output();
}