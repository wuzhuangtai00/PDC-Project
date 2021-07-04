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

const double eps = 1e-2;
const int maxn = 88000;
float a[maxn][maxn], res[maxn][maxn];
vector<pair<int,double> > Lh[maxn], Ur[maxn];

inline void init() {
    read(n); read(n); read(m);
	// memset(a, 0, sizeof(a));
	// memset(res, 0, sizeof(res));
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        a[x][y] = z;
		a[y][x] = z;
    }
	fscanf(l, "%d", &n);
	int x, y; double z;
	while(fscanf(l, "%d %d %lf", &x, &y, &z)!=EOF) {
		Lh[y].pb(mk(x, z));
		// l[x][y] = z;
	}
	fscanf(u, "%d", &n);
	while(fscanf(u, "%d %d %lf", &x, &y, &z)!=EOF) {
		Ur[x].pb(mk(y, z));
	}
}
int cur[maxn];
inline void solve() {
	rep(j, 1, n) {
		for(pair<int,double> x: Lh[j]) for(pair<int,double> y: Ur[j]) {
			res[x.w1][y.w1] += (float)x.w2 * (float)y.w2;
		}
	}
	bool flag = 1;
	rep(i, 1, n) rep(j, 1, n) {
		if (fabs((res[i][j] - a[i][j]) / max(fabs(a[i][j]), (float)	
		1.)) > eps) {
			printf("%.10f %.10f\n", res[i][j], a[i][j]);
			flag = 0; break;
		}
	}
	if(flag)puts("Correct!");else puts("Error(");
}
struct timeval starts, endsss;
int main(int argc, char** argv) {
	gettimeofday(&starts, NULL);
	puts(argv[0]);
	freopen(argv[1], "r", stdin);
	l = fopen(argv[2], "r");
	u = fopen(argv[3], "r");

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

	fclose(l);
	fclose(u);
	// output();
}