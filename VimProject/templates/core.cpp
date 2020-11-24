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
<<<<<<< HEAD
double current_time() { return (double)(chrono::steady_clock::now() - cl).count() / 1e9; }
=======
double current_time() { return (chrono::steady_clock::now() - cl).count() / 1e9; }
>>>>>>> 78789114b3861207492425bb09e00d0cc282344c
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
