#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<vector>
#include<set>
#include<cmath>
#include<sys/time.h>
#include<omp.h>
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
int cur[maxn], parent[maxn], nmsl[maxn], vvv[maxn];
inline void solve() {
	static int a[maxn], b[maxn], c[maxn];
	rep(i, 1, n) a[i] = b[i] = rand();
	#pragma omp parallel for num_threads(12)
	rep(i, 1, 10 * n * n) c[i % n] = a[i % n] + b[i % n];
	rep(i, 1, n) fprintf(l, "%d\n", c[i]);

}
struct timeval starts, endsss;
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