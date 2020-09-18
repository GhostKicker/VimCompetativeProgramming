#include "bits/stdc++.h"
//#define int ll
#define F first
#define S second
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << (x) << endl)
#define OUT(x) ((cout << (x)), exit(0))
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
//------------------------------------------//

int dp[105][105];
int mat[105][105];


int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    for (int i = 0; i < 100; ++i){
        for (int j = 0; j <= i; ++j){
            cin >> mat[i][j];
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + mat[i][j]);
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + mat[i][j]);
        }
    }
    int res = 0;
    for (int i = 0; i < 103; ++i){
        res = max(res, dp[100][i]);
    }
    cout << res;

    return 0;
}
