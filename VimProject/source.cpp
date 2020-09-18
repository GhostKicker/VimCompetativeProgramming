<<<<<<< HEAD
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
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
//------------------------------------------//

int dp[105][105];
int mat[105][105];


int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    for (int i = 0; i < 100; ++i){
        for (int j = 0; j <= i; ++j){
            cin >> mat[i][j];
            dp[i+1][j] = max(dp[i+1][j], dp[i][j] + mat[i][j]);
            dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + mat[i][j]);
        }
    }
    int res = 0;
    for (int i = 0; i < 103; ++i){
        res = max(res, dp[100][i]);
    }
    cout << res;

    return 0;
}
=======
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
[[maybe_unused]]const int maxm = 5 * 1000 + 100;
[[maybe_unused]]const int maxn = 1000 + 100;
//------------------------------------------//

bool cmp(array<int, 4> a, array<int,4> b){
    return a[0] - a[1] < b[0] - b[1];
}

pair<int,int> bal(string s){
    pair<int,int> res(0,inf);
    for (auto& it : s){
        if (it == '(') res.F++;
        else res.F--;
        res.S = min(res.S, res.F);
    }
    return res;
}

vector<pair<string, int>> pos;
vector<pair<string, int>> neg;

//minbal, bal, length, index
vector<array<int, 4>> posa;
vector<array<int, 4>> nega;

pair<int, int> dp[maxn][maxm];


int32_t main(){
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif
    fill(&dp[0][0], &dp[maxn][0], pair<int,int>(0, -2));
    dp[0][0].S = -1;

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        string s; cin >> s;
        if (bal(s).F >= 0) pos.push_back(mp(s, i));
        if (bal(s).F < 0) neg.push_back(mp(s, i));
    }

    for (auto& it : pos){
        array<int, 4> ar;
        auto cur = bal(it.F);
        ar[0] = cur.S;
        ar[1] = cur.F;
        ar[2] = it.F.size();
        ar[3] = it.S;
        posa.push_back(ar);
    }
    for (auto& it : neg){
        array<int, 4> ar;
        auto cur = bal(it.F);
        ar[0] = cur.S;
        ar[1] = cur.F;
        ar[2] = it.F.size();
        ar[3] = it.S;
        nega.push_back(ar);
    }

    sort(all(posa));
    reverse(all(posa));
    sort(all(nega), cmp);

    vector<array<int, 4>> ar;
    for (auto& it : posa) ar.push_back(it);
    for (auto& it : nega) ar.push_back(it);

    for (int i = 0; i < (int)ar.size(); ++i){
        for (int j = 0; j < maxm; ++j){
            if (dp[i][j].S == -2) continue;
            dp[i+1][j] = max(dp[i+1][j], mp(dp[i][j].F, j));
            if (j + ar[i][0] < 0) continue;
            if (j + ar[i][1] >= maxm) continue;
            pair<int,int> cur(dp[i][j].F + ar[i][2], j);
            dp[i+1][j+ar[i][1]] = max(dp[i+1][j+ar[i][1]], cur);
        }
    }

    int cur = 0;
    vector<int> path;

    for (int i = (int)ar.size(); i > 0; --i){
        if (dp[i][cur].S == -1) break;
        if (dp[i][cur].F == dp[i-1][dp[i][cur].S].F) continue;
        path.push_back(ar[i-1][3]);
        cur = dp[i][cur].S;
    }

    //for (int i = 0; i <= n; ++i){
    //    for (int j = 0; j < 10; ++j) 
    //        cout << dp[i][j].F << " ";
    //    cout << endl;
    //}
    //cout << endl;
    //for (int i = 0; i <= n; ++i){
    //    for (int j = 0; j < 10; ++j) 
    //        cout << dp[i][j].S << " ";
    //    cout << endl;
    //}
    //cout << endl;


    reverse(all(path));
    cout << dp[n][0].F << " ";
    cout << path.size() << endl;
    for (auto& it : path) cout << it+1 << " ";

    return 0;
}
>>>>>>> f22942ecca212b77c4dda28c8ea8a9e20aaed2c2
