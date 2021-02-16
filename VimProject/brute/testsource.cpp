#ifndef _MY
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx,tune=native")
#endif
#include "bits/stdc++.h"
//#define int ll
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (double)(chrono::steady_clock::now() - cl).count() / 1e9; }
//------------------------------------------//

int good[3050][3050];
int used[3050][3050];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};


int32_t main(){
    cl = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    fill(&good[0][0], &good[3050][0], 1);
    int res = 0;
    int rows, cols, n;
    cin >> rows >> cols >> n;
    for (int i = 0; i < n; ++i){
        fill(&used[0][0], &used[3050][0], 0);
        int r, c;
        cin >> r >> c;
        --r; --c;
        good[r][c] = 0;
        for (int cc = 0; cc < cols; ++cc){
            if (good[0][cc] == 0) continue;
            if (used[0][cc]) continue;
            function<void(int, int)> dfs = [&](int r, int c){
                used[r][c] = 1;
                for (int i = 0; i < 4; ++i){
                    int nr = r+dr[i];
                    int nc = (c+dc[i]+cols) % cols;
                    if (nr < 0) continue;
                    if (nr >= rows) continue;
                    if (good[nr][nc] == 0) continue;
                    if (used[nr][nc]) continue;
                    dfs(nr, nc);
                }
            };
            dfs(0, cc);
        }
        bool flag = false;
        for (int cc = 0; cc < cols; ++cc){
            if (used[rows-1][cc] == 0) continue;
            flag = true;
            break;
        }
        good[r][c] = (1-flag);
        res += flag;
        //for (int i = 0; i < rows; ++i){
        //    for (int j = 0; j < cols; ++j)
        //        cout << used[i][j];
        //    cout << endl;
        //}
        //cout << endl;
    }
    cout << res;

    return 0;
}
