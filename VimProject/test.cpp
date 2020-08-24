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
[[maybe_unused]]const int64_t INF = (int64_t)(2e18);
[[maybe_unused]]const int inf = (int)(1e9 + 7);
[[maybe_unused]]const int maxn = 500 * 1000 + 100;
//------------------------------------------//



vector<vector<int>> g;
vector<int> dp;

int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    //freopen("VimProject/output.txt", "w", stdout);
#endif

    int n;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n-1; ++i){
        int f, t;
        cin >> f >> t;
        --f;--t;
        g[f].push_back(t);
        g[t].push_back(f);
    }
    int s;
    queue<int> q;

    s = 0;
    dp.assign(n, inf);
    dp[s] = 0;
    q.push(0);
    while(q.size()){
        int v = q.front();
        q.pop();
        for (auto& it : g[v]){
            if (dp[it] != inf) continue;
            dp[it] = dp[v]+1;
            q.push(it);
            s = it;
        }
    }

    dp.assign(n, inf);
    dp[s] = 0;
    
    q.push(s);
    while(q.size()){
        int v = q.front();
        q.pop();
        for (auto& it : g[v]){
            if (dp[it] != inf) continue;
            dp[it] = dp[v]+1;
            q.push(it);
            s = it;
        }
    }

    cout << *max_element(all(dp));

    return 0;
}
