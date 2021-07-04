#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#include<map>
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

const int n = 3000;
const int maxn = 10005;
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];

int main(){
	srand(time(NULL));
	rep(i, 1, n) rep(j, 1, i) {
		if(rand() % 100 == 0){
			int w = rand() % 100 + 1;
			a[i][j] = b[j][i] = w;
		}
	}
	rep(i, 1, n) rep(j, 1, n) rep(k, 1, n) c[i][k] += a[i][j] * b[j][k];
	vector<pair<pair<int,int>,int> > v;
	rep(i, 1, n) rep(j, 1, i) {
		if (c[i][j]) v.pb(mk(mk(i, j), c[i][j]));
	}
	printf("%d %d %d\n", n, n, (int)v.size());
	for(auto x:v) {
		printf("%d %d %d\n", x.w1.w1, x.w1.w2, x.w2);
	}
}