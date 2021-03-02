#ifndef _MY
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx,tune=native")
#endif
//#define _GLIBCXX_DEBUG
#include "bits/stdc++.h"
#define F first
#define S second
#define mp make_pair
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
clock_t cl;
double current_time() { return double(clock() - cl) / CLOCKS_PER_SEC; }
//------------------------------------------//




int32_t main(){
    cl = clock();
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    cout << CLOCKS_PER_SEC << endl;
    int res = 0;
    for (int i = 0; i < 1000000000; ++i) res += i;
    cerr << res << endl;
    cout << current_time();


    return 0;
}
