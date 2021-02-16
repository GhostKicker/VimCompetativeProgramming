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

    mt19937_64 rng(seed);

#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    int n = 10;
    int m = 10;
    int q = 80;
    cout << n << " " << m << " " << q << endl;
    set<pair<int,int>> s;
    while(q > 0){
        int r = rng() % n + 1;
        int c = rng() % m + 1;
        if (s.count(make_pair(r, c))) continue;
        cout << r << " " << c << endl;
        s.insert(make_pair(r, c));
        --q;
    }
    


    return 0;
}
