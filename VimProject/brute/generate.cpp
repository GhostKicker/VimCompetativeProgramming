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

    int n = 1000;
    cout << n << endl;
    for (int i = 0; i < n; ++i) cout << rng() % n + inf << " ";
    cout << endl;

    vector<pair<int,int>> e;
    for (int i = 1; i < n; ++i){
        e.push_back(make_pair(i, rng()%i));
        if (rng() % 2) swap(e.back().second, e.back().first);
    }
    shuffle(all(e), rng);
    for (auto& it : e) cout << it.first + 1 << " " << it.second + 1 << endl;

    return 0;
}
