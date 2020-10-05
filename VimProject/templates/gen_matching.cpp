#include <bits/stdc++.h>
 
#ifdef HOME
#define db(x) cerr << #x << " = " << x << endl
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")" << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")" << endl
#define dbv(a) cerr << #a << " = "; for (auto xxx: a) cerr << xxx  << " "; cerr << endl
#else
#define db(x) ;
#define db3(x, y, z) ;
#define db2(x, y) ;
#define dbv(a) ;
#endif
 
using namespace std;
typedef long long ll;
typedef double dbl;
 
 
const int INF = 1.01e9;
 
void print(vector<pair<int, int>> a) {
    cout << 2 * a.size() << endl;
    for (auto o : a) cout << o.first + 1 << " " << o.second + 1 << endl;
}
 
vector<pair<int, int>> solve(int n, vector<pair<int, int>> ed) {
    vector<vector<int>> e(n);
    for (auto o : ed) {
        e[o.first].push_back(o.second);
        e[o.second].push_back(o.first);
    }
 
    vector<int> mt(n, -1);
    vector<int> vis(n);
    int tmr = 0;
 
    function<int(int)> dfs = [&](int v) {
        if (vis[v] == tmr) return 0;
        random_shuffle(e[v].begin(), e[v].end());
        vis[v] = tmr;
        for (int to : e[v]) {
            int oth = mt[to];
            if (oth == -1) {
                mt[to] = v;
                mt[v] = to;
                return 1;
            }
            if (vis[oth] == tmr) continue;
            mt[v] = to;
            mt[to] = v;
            mt[oth] = -1;
            if (dfs(oth)) return 1;
            mt[oth] = to;
            mt[to] = oth;
            mt[v] = -1;
        }
        return 0;
    };
 
    while (clock() / (double)CLOCKS_PER_SEC < 0.3) {
        for (int i = 0; i < n; i++) {
            if (mt[i] != -1) continue;
            tmr++;
            dfs(i);
        }
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) if (mt[i] > i) ans.push_back({i, mt[i]});
    return ans;
}
 
int main() {
#ifdef HOME
    assert(freopen("in", "r", stdin));
#endif
 
    int n;
    cin >> n;
    vector<pair<int, int>> ed;
    int u, v;
    while (cin >> u >> v) ed.push_back({u - 1, v - 1});
 
    print(solve(n, ed));
 
#ifdef HOME
    cerr << "time: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
#endif
}
