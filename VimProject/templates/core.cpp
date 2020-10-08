#include "bits/stdc++.h"
#include <chrono>
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
chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (chrono::steady_clock::now() - cl).count() / 1e9; }
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


    return 0;
}
