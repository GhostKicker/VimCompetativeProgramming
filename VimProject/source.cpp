#include "bits/stdc++.h"
#define int ll
#define F first
#define S second
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << (x) << endl)
#define OUT(x) ((cout << (x)), exit(0))
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
//------------------------------------------//


void go(set<int>& s, vector<pair<int,int>>& v, int ind, int cur, int curres = 1){
    if (ind == (int)v.size()) {
        if (!s.count(curres)) return;
        cout << curres << " ";
        s.erase(curres);
        return;
    }
    for (int i = 0; i <= v[ind].S; ++i, curres *= v[ind].F){
        if (cur == 0 && i == 0) continue;
        go(s, v, ind+1, cur+1, curres);
    }
}

void solve(){
    set<int> divi;
    map<int, int> pr;
    int n;
    cin >> n;
    for (int i = 1; i*i <= n; ++i){
        if (n % i == 0){
            if (i != 1) divi.insert(i);
            divi.insert(n / i);
        }
    }
    for (int i = 2; i * i <= n; ++i){
        while (n % i == 0){
            pr[i]++;
            n /= i;
        }
    }
    if (n != 1) pr[n]++;

    if (pr.size() == 1){
        for (auto& it : divi) cout << it << " ";
        cout << endl << 0 << endl;
        return;
    }

    int cnt = 0;
    for (auto& it : pr){
        cnt += it.second;
    }
    if (cnt < 3){
        for (auto& it : divi) cout << it << " ";
        cout << endl << 1 << endl;
        return;
    }

    vector<int> lnk;
    for (auto& it : pr) lnk.push_back(it.first);

    vector<pair<int,int>> kek;
    for (auto& it : pr) kek.push_back(it);
    for (int i = 0; i < (int)lnk.size(); ++i){
        divi.erase(lnk[i]*lnk[(i + 1) % (int)lnk.size()]);
    }

    for (int i = 0; i < (int)kek.size(); ++i){
        go(divi, kek, i, 0ll);
        cout << lnk[i]*lnk[(i + 1) % (int)lnk.size()] << " ";
    }
    cout << endl << 0 << endl;


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
