#include <bits/stdc++.h>
//#define int int64_t
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << x << endl)
#define OUT(x) ((cout << x), exit(0))
using namespace std;
typedef long double db;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
//------------------------------------------//

const int maxn = 3000 * 100 + 10;
int curtime = 0;

int color_edge[maxn];
int tin[maxn];
int fup[maxn];
int added[maxn];
vector<pair<int,int>> g[maxn];
vector<int> g1[2 * maxn];

vector<int> cuts;
bool is_cut(int v) {
    auto it = lower_bound(all(cuts), v);
    if (it == cuts.end()) return false;
    if (*it != v) return false;
    return true;
}
void dfs_cuts(int v, int root) {
    fup[v] = tin[v] = ++curtime;
    int sons = 0;
    bool is_cut = false;
    for (auto e : g[v]) {
        if (tin[e.first]) fup[v] = min(fup[v], tin[e.first]);
        else {
            ++sons;
            dfs_cuts(e.first, root);
            fup[v] = min(fup[v], fup[e.first]);
            if (fup[e.first] >= tin[v]) is_cut = 1;
        }
    }
    if (v == root && sons > 1) cuts.push_back(v);
    if (v != root && is_cut) cuts.push_back(v);
}

vector<pair<int, int>> edges;
int used[maxn];
set<int> comps[maxn];
int newcol = -1;
void dfs_color(int v, int color, int par) {
    used[v] = 1;
    for (auto& e : g[v]) {
        if (e.first == par) continue;

        if (used[e.first] && tin[e.first] < tin[v])
            color_edge[e.second] = color;
        if (used[e.first]) continue;

        if (fup[e.first] >= tin[v]) {
            color_edge[e.second] = ++newcol;
            dfs_color(e.first, newcol, v);
        }
        else {
            color_edge[e.second] = color;
            dfs_color(e.first, color, v);
        }
    }
}

set<int> res;
bool dfs_find(int v, int goal) {
    used[v] = 1;
    if (v == goal) return true;
    bool good = false;
    for (auto& to : g1[v]) {
        if (used[to]) continue;
        good |= dfs_find(to, goal);
    }
    if (good && v < cuts.size())
        res.insert(cuts[v]);
    return good;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n, m; 
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        edges.push_back({ a, b });
        g[a].push_back({ b, i });
        g[b].push_back({ a, i });
    }

    for (int i = 0; i < n; ++i) {
        if (tin[i]) continue;
        dfs_cuts(i, i);
    }

    newcol = (int)cuts.size() - 1;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        dfs_color(i, newcol, i);
    }

    sort(all(cuts));
    for (int i = 0; i < m; ++i) {
        int u = edges[i].first;
        int v = edges[i].second;
        added[u] = 1;
        added[v] = 1;
        if (is_cut(u)) {
            int iu = int(lower_bound(all(cuts), u) - begin(cuts));
            int iv = color_edge[i];
            g1[iu].push_back(iv);
            g1[iv].push_back(iu);
        }
        swap(u, v);
        if (is_cut(u)) {
            int iu = int(lower_bound(all(cuts), u) - begin(cuts));
            int iv = color_edge[i];
            g1[iu].push_back(iv);
            g1[iv].push_back(iu);
        }
    }

    int nn = (int)cuts.size() + newcol + 1;
    for (int i = 0; i < nn; ++i) {
        sort(all(g1[i]));
        g1[i].resize(unique(all(g1[i])) - begin(g1[i]));
    }

    for (int i = 0; i < m; ++i) {
        comps[edges[i].first].insert(color_edge[i]);
        comps[edges[i].second].insert(color_edge[i]);
    }
    for (int i = 0; i < n; ++i) {
        if (added[i]) continue;
        comps[i].insert(++newcol);
    }

    int q;
    cin >> q;
    while (q--) {
        int f, t;
        cin >> f >> t;
        --f; --t;
        fill(used, used + nn, 0);
        int u = *comps[f].begin();
        int v = *comps[t].begin();
        res.clear();
        dfs_find(u, v);
        res.erase(f);
        res.erase(t);
        cout << res.size() << endl;
        
    }



    return 0;
}
