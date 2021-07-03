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

const int maxn = 83334;
int n, m;   
namespace union{
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
int parent[maxn]; //The father in the elinimation tree.

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        if(x < y) swap(x, y);
        pos[x].pb(mk(y, z));
    }
    union::init(n);
    rep(i, 1, n) {
        sort(pos[i].begin(), pos[i].end());
    }
}

inline void solve() {
    
}

inline void check_ans() {

}


int main() {
	clock_t pre = clock();

    init();

	printf("Init: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

    solve();

	printf("Solve: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

	check_ans();

	printf("Check Ans: %.4f\n", (clock() - pre)/(double)CLOCKS_PER_SEC);
	pre = clock();

	// output();
}