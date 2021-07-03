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

inline void init() {
    read(n); read(n); read(m);
    rep(i, 1, m) {
        int x, y; double z;
        read(x); read(y); scanf("%lf", &z);
        
    }
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