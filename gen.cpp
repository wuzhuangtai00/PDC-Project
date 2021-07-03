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

const int n = 3;
const int maxn = 105;
int a[maxn][maxn], b[maxn][maxn], c[maxn][maxn];

int main(){
	srand(time(NULL));
	rep(i, 1, n) rep(j, 1, i) {
		int w = rand() % 3;
		a[i][j] = b[j][i] = w;
	}
	rep(i, 1, n) rep(j, 1, n) rep(k, 1, n) c[i][k] += a[i][j] * b[j][k];
	printf("%d %d %d\n", n, n, n * (n + 1) / 2);
	rep(i, 1, n) rep(j, 1, i) {
		printf("%d %d %d\n", i, j, c[i][j]);
	}
	rep(i, 1, n) {
		rep(j, 1, n) {
			fprintf(stderr, "%d ", a[i][j]);
		}
		fprintf(stderr, "\n");
	}
	rep(i, 1, n) {
		rep(j, 1, n) {
			fprintf(stderr, "%d ", c[i][j]);
		}
		fprintf(stderr, "\n");
	}
}