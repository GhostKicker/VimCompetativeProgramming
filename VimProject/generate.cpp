#include <bits/stdc++.h>
#include <chrono>
//#define int ll
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << (x) << endl)
#define OUT(x) ((cout << (x)), exit(0))
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 100 * 1000 + 100;
//------------------------------------------//

mt19937 rng(time(0));
int maxsz = 10;
void solve(){
    int n = rng() % (maxsz - 1) + 1;
    int m = maxsz - n;
    cout << n << " " << m << endl;
    string res;
    for (int i = 0; i < maxsz; ++i){
        res.push_back('0' + rng() % 2);
    }
    cout << res << endl;
}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    //freopen("VimProject/input.txt", "w", stdout);
#endif
    unsigned long long milliseconds_since_epoch =
    std::chrono::system_clock::now().time_since_epoch() / 
    std::chrono::milliseconds(1);
    mt19937 rng(milliseconds_since_epoch);
    int t = 1;
    cout << t << endl;
    for (int test = 0; test < t; ++test) solve();

    return 0;
}
