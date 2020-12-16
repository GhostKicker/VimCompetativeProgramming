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

struct node{
    int left = 0;
    int right = 0;
    int key = 0;
    int count = 0;
    int minn = 2*inf;
    int maxx = 2*-inf;
    node(){}
};
vector<node> tr;

void dfs(int v){
    if (v == 0) return;
    tr[v].count = 1;
    tr[v].minn = tr[v].key;
    tr[v].maxx = tr[v].key;

    dfs(tr[v].left);
    dfs(tr[v].right);
    tr[v].count += tr[tr[v].left].count;
    tr[v].count += tr[tr[v].right].count;
    tr[v].minn = min(tr[v].minn, tr[tr[v].left].minn);
    tr[v].minn = min(tr[v].minn, tr[tr[v].right].minn);
    tr[v].maxx = max(tr[v].maxx, tr[tr[v].left].maxx);
    tr[v].maxx = max(tr[v].maxx, tr[tr[v].right].maxx);
}

int cur = 0;
int lookup(int v, int l, int r){
    ++cur;
    if (v == 0) return 0;
    if (l <= tr[v].minn && tr[v].maxx <= r) return tr[v].count;
    if (tr[v].maxx < l || r < tr[v].minn) return 0;
    int res = 0;
    if (l <= tr[v].key && tr[v].key <= r) ++res;
    res += lookup(tr[v].left, l, r);
    res += lookup(tr[v].right, l, r);
    return res;
}


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
    tr.resize(n+1);

    for (int i = 1; i <= n; ++i){
        cin >> tr[i].left >> tr[i].right;
        cin >> tr[i].key;
    }
    dfs(1);

    int q; 
    cin >> q;


    for (int qq = 0; qq < q; ++qq){
        cur = 0;
        int l, r;
        cin >> l >> r;
        lookup(1, l, r);
        cout << cur << "\n";
    }


    return 0;
}
