chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (double)(chrono::steady_clock::now() - cl).count() / 1e9; }

vector<pair<int, int>> matching(int n, vector<pair<int, int>> ed) {
    auto sttm = current_time();
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
 
    while (current_time() - sttm < 0.3) {
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
