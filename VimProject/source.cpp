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


void solve(){
    int n, m;
    cin >> n >> m;
    int nn = n;
    int mm = m;
    string s;
    cin >> s;
    int i0 = (int)s.size();
    int i1 = (int)s.size();
    vector<int> nextdif(s.size() + 1, 0);
    nextdif.back() = i0;
    for (int i = (int)s.size() - 1; i >= 0; --i){
        if (s[i] == '0') nextdif[i] = i1;
        if (s[i] == '1') nextdif[i] = i0;
        if (s[i] == '0') i0 = i;
        if (s[i] == '1') i1 = i;
    }
    string ns, ms;
    if (n < m) swap(n, m);
    for (int i = 0; i < (int)s.size(); ++i){
        if (s[i] == '1'){
            int st0 = nextdif[i];
            int st1 = nextdif[st0];
            int st0n = nextdif[st1];
            if (/*st0 - i == 1 &&*/ st0n - st1 >= st0 - i && m >= st1 - i){
                for (int j = i; j < st1; ++j){
                    ms.push_back(s[j]); --m;
                }
                i = st1-1;
            }
            else {
                ns.push_back(s[i]); --n;
            }
        }
        else {
            if (m){
                ms.push_back(s[i]);
                --m;
            } else {
                ns.push_back(s[i]);
                --n;
            }
        }
        if (n < m){
            swap(n, m);
            swap(ns, ms);
        }
    }
    if (ns < ms) swap(ns, ms);
    cout << ns << endl; 
    cout << ms << endl;
    reverse(all(ns));
    reverse(all(ms));
    while(ns.size() < ms.size()) ns.push_back('0');
    while(ns.size() > ms.size()) ms.push_back('0');
    ns.push_back('0');
    ms.push_back('0');
    string res;
    for (int i = 0; i < (int)ns.size(); ++i){
        res.push_back(ns[i] - '0' + ms[i]);
    }
    for (int i = 0; i < (int)res.size() ; ++i){
        if (res[i] >= '2'){
            res[i] -= 2;
            res[i+1] ++;
        }
    }
    while((int)res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(all(res));
    cout << res << endl;
    if (n < 0 || m < 0) throw "";
    if ((int)res.size() > nn + mm) throw "";

    cout << endl;
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
