#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<omp.h>
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
int cur[maxn];
inline void solve() {
	rep(i, 1, n) {
		// printf("!%d\n", i);
		vector<int> nz; nz.clear();
		per(j, n, i) if (fabs(a[i][j]) > eps) nz.pb(j);
		int sz = (int)nz.size() - 1;
		if(fabs(a[i][i]) < eps) continue;
		int cnt = 0;
		rep(k, i + 1, n) {
			if(fabs(a[k][i]) > eps) cur[++cnt] = k;
		}
// #pragma omp parallel for num_threads(12) schedule(dynamic, 1)
		rep(j, 1, cnt) {
			int k = cur[k];
			double d = a[k][i] / a[i][i];
			// #pragma omp for
			for(int j = 0;  <= sz; j++) {
				a[k][nz[j]] -= a[i][nz[j]] * d;
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