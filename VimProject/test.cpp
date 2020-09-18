#include "bits/stdc++.h"
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
[[maybe_unused]]const int64_t INF = (int64_t)(2e18);
[[maybe_unused]]const int inf = (int)(1e9 + 7);
[[maybe_unused]]const int maxn = 500 * 1000 + 100;
//------------------------------------------//

string sum(string a, string b){
    string res;
    reverse(all(a));
    reverse(all(b));
    while(a.size() < b.size()) a.push_back('0');
    while(a.size() > b.size()) b.push_back('0');
    a.push_back('0');
    b.push_back('0');
    for (int i = 0; i < (int)a.size(); ++i)
        res.push_back(a[i] - '0' + b[i]);
    for (int i = 0; i < (int)res.size(); ++i)
        if (res[i] >= '2') {
            res[i] -= 2;
            res[i+1]++;
        }
    while((int)res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(all(res));
    return res;
}

bool cmp(string a, string b){
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

void solve(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    string ra, rb;
    string res;
    for (int mask = 0; mask < (1 << (n + m)); ++mask){
        if (__builtin_popcount(mask) != n) continue;
        string a, b;
        for (int bit = 0; bit < n+m; ++bit){
            if ((mask >> bit) & 1) a.push_back(s[bit]);
            else b.push_back(s[bit]);
        }
        string curres = sum(a, b);
        if (cmp(res, curres)){ 
            swap(res, curres);
            ra = a;
            rb = b;
        }
    }
    if (ra < rb) swap(ra, rb);
    cout << ra << endl;
    cout << rb << endl;
    cout << res << endl;

}


int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    int t;
    cin >> t;
    while(t--) solve();


    return 0;
}
