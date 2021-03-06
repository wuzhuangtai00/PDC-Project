#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<map>
#include<vector>
#include<set>
#include<cmath>
#include<cassert>
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
#define pb push_back
#define mk make_pair
#define w1 first
#define w2 second

typedef pair<int,int> pin;

const double eps = 1e-3;
typedef pair<int, double> info;
const int maxm = 2000000000;
info pool1[6000000000ll];
info *ptr;
set<pin> rec;

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

const int maxn = 86334;
int n, m;
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

vector<pair<int,double> > pos[maxn];
vector<pair<int,double> > all[maxn];
int parent[maxn]; //The father in the elinimation tree.
map<int, double> w[maxn];

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        if(fabs(z) <= eps) continue;
        if(x < y) swap(x, y);
        w[x][y] = z;
        w[y][x] = z;
        assert(fabs(z) > 1e-8);
        pos[x].pb(mk(y, z));
        rec.insert(mk(x, y));
    }
    unions::init(n);
    rep(i, 1, n) {
        // sort(all[i].begin(), all[i].end());
        sort(pos[i].begin(), pos[i].end());
    }
    ptr = pool1;
}

vector<int> son[maxn];

int stpos[maxn];

int size[maxn];


info* Left[maxn];
info* Right[maxn];
int upper[maxn];

clock_t pre;


bool vis[maxn];

long long cnt = 0;

inline info* mlc(int sz) {
    cnt += sz;
    if(cnt > 6000000000ll) {
        // ptr = pool2;
        assert(0);
    }
    info* tmp = ptr;
    ptr = ptr + sz;
    return tmp;
}

inline void dfs(int x, int sz) {
    vis[x] = 1; upper[x] = sz;
    // printf("%d\n", size[x]);
    // assert(sz <= n);
    Left[x] = (info*)mlc(size[x]);
    Right[x] = (info*)mlc(sz);
    if(parent[x]){
        rep(i, 0, sz - 2) Right[x][i] = Right[parent[x]][i];
        Right[x][sz - 1] = mk(parent[x], 0);
    }
    Left[x][0] = mk(x, 0);
    int cur = 1;
    for(auto y: son[x]) {
        dfs(y, sz + 1);
        stpos[y] = cur; cur += size[y];
        rep(i, stpos[y], cur - 1) {
            Left[x][i] = Left[y][i - stpos[y]];
        }
    }
}
pair<pin, double> U[50000000];
int cntL, cntU;
int poshis[maxn];

inline void printLeft(int x, int y) {
    printf("Left[%d][%d].w1 = %d Left[%d][%d].w2 = %.3f, Size [%d] = %d\n", x, y, Left[x][y].w1, x, y, Left[x][y].w2, x, size[x]);
}

inline void printRight(int x, int y) {
    printf("Right[%d][%d].w1 = %d Right[%d][%d].w2 = %.3f, RightSize [%d] = %d\n", x, y, Right[x][y].w1, x, y, Right[x][y].w2, x, upper[x] - 1);
}
inline void solve() {
    rep(i, 1, n) {
        for(auto x: pos[i]) {
            int y = x.w1;
            int w = unions::find(y);
            if(w == i) continue;
            // printf("%d %d\n", w, i);
            parent[w] = i;
            son[i].pb(w);
            unions::setfa(w, i);
        }
    }
    rep(i, 1, n) size[i] = 1;
    rep(i, 1, n) if(parent[i]) size[parent[i]] += size[i];
    // int ppp = 0;
    // rep(i, 1, n) ppp += size[i];
    // printf("%d\n", ppp);
    // return;
    per(i, n, 1) {
        if (vis[i]) continue;
        dfs(i, 0);
    }
    // rep(i, 1, n) {
        // printf("%d %d\n", stpos[i], parent[i]);
    // }
    printf("Block1: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
    printf("Total Used: %lld\n", cnt);

    rep(i, 1, n) {
        unsigned j = 0;
        rep(k, 0, size[i] - 1) {
            if (w[i].count(Left[i][k].w1)) Left[i][k].w2 = w[i][Left[i][k].w1];
        }
        rep(k, 0, upper[i] - 1) {
            if (w[i].count(Right[i][k].w1)) Right[i][k].w2 = w[i][Right[i][k].w1];
        }
    }

    printf("Block2: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);

    rep(x, 1, n) {
        assert(Left[x][0].w2 > 0);
        double www = sqrt(Left[x][0].w2);
        cntU++;
        U[cntU] = mk(mk(x, x), www);
        // printRight(1, 0);
        vector<int> nz; nz.clear();
        rep(k, 0, upper[x] - 1) {
            info w = Right[x][k];
            if(fabs(w.w2) > 1e-7) {
                cntU++;
                U[cntU] = mk(mk(x, w.w1), w.w2 / www);
                nz.pb(k);
            }
        }
        int y = parent[x];
        int curpos = stpos[x];

        int poscnt = 0;
        if(fabs(Left[x][0].w2) < 1e-9) continue;
        while(y) {
            // printf("%d\n", y);
            poshis[++poscnt] = y;
            // printf("Size:%d\n", size[y]);
            // printLeft(y, 0);
            // printLeft(y, 1);
            // printf("%d %d %.3f\n",Left[y][curpos].w1, x, Left[y][curpos].w2);
            // putchar('!');printLeft(y, curpos);
            double d = Left[y][curpos].w2 / Left[x][0].w2;
            if (fabs(d) > 1e-8) {
                cntL++;
                // printf("%.10f %.10f\n", Left[y][curpos].w2, Left[x][0].w2);
                // printf("%.10f\n", d);
                for(unsigned i = 0; i < nz.size(); i++) {
                    int k = nz[i]; if (k >= upper[y]) break;
                    Right[y][k].w2 -= Right[x][k].w2 * d;
                }
                int wpos = 0; int iter = poscnt - 1;
                // printf("%d %d\n", upper[x], upper[y]);
                rep(i, upper[y], upper[x] - 1) {
                    // printf("%d %d\n", Left[y][wpos].w1, Right[x][i].w1);
                    // assert(Left[y][wpos].w1 == Right[x][i].w1);
                    Left[y][wpos].w2 -= Right[x][i].w2 * d;
                    // printLeft(y, wpos);
                    wpos += stpos[poshis[iter]];
                    iter--;
                }
                // printf("?%d\n", curpos);
                Left[y][curpos].w2 -= Left[x][0].w2 * d;
                // printLeft(3, 1);
            }

            curpos += stpos[y];
            y = parent[y];
            // printf("???%d\n", stpos[y]);
        }
    }
}
/*
inline void check_ans() {
    static vector<pair<int, double> > Ls[maxn], Ul[maxn];
	rep(i, 1, cntL) {
		pair<pin, double> x = L[i];
        Ls[x.w1.w2].pb(mk(x.w1.w1, x.w2));
	}
    rep(i, 1, cntU) {
        pair<pin, double> x = U[i];
        Ul[x.w1.w1].pb(mk(x.w1.w2, x.w2));
    }

	rep(j, 1, n) {
		for(auto i: Ls[j]) for(auto k: Ul[j]) {
			w[i.w1][k.w1] -= i.w2 * k.w2;
		}
	}
	bool flag = 1;
    rep(i, 1, n) {
        for(pair<int, double> v : w[i]) {
            if(fabs(v.w2) > eps) {
                flag = 0;
                printf("%d %d %.10f\n", i, v.w1, v.w2);
            }
        }
    }
	// printf("%d\n", flag);
    if(flag)
        puts("Correct!");
    else
        puts("Error!");
}

inline void output() {

	printf("%d\n", cntL);
	rep(i, 1, cntL) {
		pair<pin, double> x = L[i];
		printf("%d %d %.8f\n", x.w1.w1, x.w1.w2, x.w2);
	}

	puts("");
	printf("%d\n", cntU);
    rep(i, 1, cntU) {
		pair<pin, double> x = U[i];
		printf("%d %d %.8f\n", x.w1.w1, x.w1.w2, x.w2);
	}
}
*/
int main() {
	pre = clock();

    init();

	printf("Init: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

    solve();

	printf("Solve: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

	// check_ans();

	printf("Check Ans: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

	// output();

	printf("Output: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();


}