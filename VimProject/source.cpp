#ifndef _MY
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx,tune=native")
#endif
//#define _GLIBCXX_DEBUG
#include "bits/stdc++.h"
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

bool dp[26][1 << 15][15];

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
    sort(all(a));

    if (n == 1){
        if (a[0] == 1) cout << "YES";
        else cout << "NO";
        exit(0);
    }

    reverse(all(a));

    if (a[0] == 1) {
        cout << "NO";
        exit(0);
    }


    int leafs = 0;
    while(a.size() && a.back() == 1){
        ++leafs;
        a.pop_back();
    }


    if (leafs+2 < (n+1)/2){
        cout << "NO";
        exit(0);
    }

    n = a.size();

    int fullmask = (1 << n)-2;
    dp[0][fullmask][leafs] = 1;
    for (int i = 0; i < n; ++i){
        for (int l = 0; l <= leafs; ++l){
            for (int mask = 0; mask < (1 << n); mask+=(1 << (i+1))){
                if (dp[i][mask][l] == 0) continue;
                int submask = mask;
                do{
                    //cout << "here" << " " << l << " " << submask << endl;
                    int cntsons = __builtin_popcount(submask);
                    int usedleafs = a[i]-1;
                    for (int bit = i+1; bit < n; ++bit){
                        if ((submask >> bit) & 1) 
                            usedleafs-=a[bit];
                    }
                    //cout << usedleafs << endl;
                    if (usedleafs < 0) continue;
                    if (usedleafs > l) continue;
                    if (usedleafs == 0 && cntsons == 1) continue;
                    if (submask == 0 && usedleafs < 2) continue;
                    //cout << i+1 << " " << (mask ^ submask) << " " << l-usedleafs << endl;
                    dp[i+1][mask ^ submask][l-usedleafs] = 1;

                } while((submask=((submask-1)&mask)) != 0);
            }
        }
    }


    if (dp[n][0][0] == 1) cout << "YES";
    else cout << "NO";







    return 0;
}
