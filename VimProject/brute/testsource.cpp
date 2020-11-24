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


int whitexor(vector<int> a){
    int res = 0;
    for (auto& it : a) res ^= it;
    return res;
}

int bxor(int lesser, int cnt, int bigger = -1){
    if (bigger == -1){
        if (cnt % 2) return lesser;
        else return lesser-1;
    }else{
        if(cnt % 2) return lesser-1;
        else return lesser;
    }
}

int blackxor(vector<int> a){
    if ((int)a.size() == 0) return 0;
    sort(all(a));
    int greater = 0;
    for (int i = 0; i < (int)a.size()-1; ++i){
        if (a[i] < a[i+1]) greater = 1;
    }
    int cnt = 1;
    for (int i = 0; i < (int)a.size()-1; ++i){
        if (a[i] != a[i+1]) break;
        ++cnt;
    }
    return bxor(a[0], cnt, greater-1);
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
    vector<int> a(n);
    for (auto& it : a) cin >> it;
    int res = 0;
    for (int mask = 0; mask < (1 << n); ++mask){
        vector<int> blackgame;
        vector<int> whitegame;
        for (int bit = 0; bit < n; ++bit){
            if ((mask >> bit) & 1) blackgame.push_back(a[bit]);
            else whitegame.push_back(a[bit]);
        }
        if (whitexor(whitegame) == blackxor(blackgame)) ++res;
    }
    cout << res;

    

    return 0;
}
