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




int32_t main(){
    cl = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> res(n, 1);
    for (auto& it : a) cin >> it;
    vector<vector<int>> g(n);
    for (int i = 0; i < n-1; ++i){
        int f, t;
        cin >> f >> t;
        --t;--f;
        g[f].push_back(t);
        g[t].push_back(f);
    }

    map<int,int> m;
    function<void(int, int, int)> dfs = [&](int v, int p, int r){
        m[a[v]]++;
        if (m[a[v]] > 1) res[r] = 0;
        for (auto& it : g[v]){
            if (it == p) continue;
            dfs(it, v, r);
        }
        m[a[v]]--;
    };
    for (int i = 0; i < n; ++i){
        dfs(i, -1, i);
    }
    int result = 0;
    for (auto& it : res) result += it;
    cout << result;


    return 0;
}
