#include "bits/stdc++.h"
#define F first
#define S second
#define mp make_pair
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

    int n = 8;
    cout << n << endl;
    vector<pair<int,int>> e;
    for (int i = 1; i < n; ++i){
        e.push_back(mp(i, rng()%i));
        e.back().F++;
        e.back().S++;
    }
    shuffle(all(e), rng);
    for (auto& it : e) cout << it.F << " " << it.S << endl;
    


    return 0;
}
