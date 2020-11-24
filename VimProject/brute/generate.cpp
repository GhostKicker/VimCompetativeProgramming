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


    freopen("VimProject/brute/seed.txt", "r", stdin);
    ll seed; cin >> seed;
    fclose(stdin);

    freopen("VimProject/brute/seed.txt", "w", stdout);
    cout << seed+1;
    cout << flush;
    fclose(stdout);

    mt19937 rng(seed);

#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    int n = rng() % 5 + 1;
    cout << n << endl;
    for (int i = 0; i < n; ++i){
        cout << rng() % 5 + 1 << " ";
    }


    return 0;
}
