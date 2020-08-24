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

struct dsu{
    vector<int> s, p;
    dsu(){}
    dsu(int n){
        s.assign(n, 1);
        p.resize(n);
        iota(begin(p), end(p), 0);
    }
    int root(int v){
        if (p[v] == v) return v;
        return p[v] = root(p[v]);
    }
    bool unite(int na, int nb){
        int a = root(na);
        int b = root(nb);
        if (a == b) return false;
        if (s[a] < s[b]) swap(a, b);
        s[a] += s[b];
        p[b] = a;
        return true;
    }
};


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
    for (int i = 0; i < t; ++i){
        int n = 1000;
        cout << n << endl;
        dsu u(n);
        while(u.s[u.root(0)] != n){
            int a = rng() % n;
            int b = rng() % n;
            if (u.unite(a, b)) {
                cout << a+1 << " " << b+1 << endl;
            }
        }
    }

    return 0;
}
