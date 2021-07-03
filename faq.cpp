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
set<pin> pos;

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        a[x][y] = z;
		a[y][x] = z;
    }
}

inline void solve() {
	rep(i, 1, n) {
		vector<int> nz; nz.clear();
		per(j, n, i) if (fabs(a[i][j]) > eps) nz.pb(j);
		if(fabs(a[i][i]) < eps) continue;
		#pragma omp parallel for num_threads(12) schedule(dynamic)
		rep(k, i, n) {
			printf("%d\n", k);
			if(fabs(a[k][i]) < eps) continue; double d = a[k][i] / a[i][i];
			// #pragma omp for
			for(unsigned i = 0; i < nz.size(); i++) {
				int p = nz[i];
				a[k][p] -= a[i][p] * d;
			}
		}
	}
}
struct timeval starts, endsss;
int main() {
	gettimeofday(&starts, NULL);

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

	// output();
}