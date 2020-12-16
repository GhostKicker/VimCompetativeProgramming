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


vector<int> left(1, -1);
vector<int> right(1, -1);
vector<int> vals(1, 0);

set<int> vs;
vector<int> values;
void dfs(int v){
    if (left[v] != -1) dfs(left[v]);
    vals[v] = values.back();
    values.pop_back();
    if (right[v] != -1) dfs(right[v]);
}

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

    int n = 10;
    for (int i = 0; i < (int)left.size(); ++i){
        int curl = rng() % 3;
        int curr = rng() % 3;
        if (curl > 0 && left.size() < n) {
            left[i] = left.size();
            left.push_back(-1);
            right.push_back(-1);
            vals.push_back(0)
        }
        if (curr > 0 && right.size() < n) {
            right[i] = right.size();
            left.push_back(-1);
            right.push_back(-1);
            vals.push_back(0);
        }
    }
    n = left.size();

    while(vs.size() < n){
        vs.insert(rng() % inf - inf/2);
    }

    for (auto& it : vals){
        values.push_back(it);
    }
    reverse(all(values));
    


    return 0;
}
