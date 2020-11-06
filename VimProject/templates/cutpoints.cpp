namespace FindAllCutPoints {
    vector<int> points;
    vector<int> fup, tin;
    int tin_global = 0;

    void dfs(int cur, int parent, vector<vector<int>>& g) {
        bool is_ans = false;
        int sons = 0;
        tin[cur] = ++tin_global;
        fup[cur] = tin_global;
        for (int i = 0; i < g[cur].size(); i++) {
            int to = g[cur][i];
            if (tin[to] == 0) {
                dfs(to, cur, g);
                sons++;
                fup[cur] = min(fup[cur], fup[to]);
                if (fup[to] >= tin[cur])
                    is_ans = true;
            }
            else {
                if (to != parent) {
                    fup[cur] = min(fup[cur], tin[to]);
                }
            }
        }
        if ((cur != parent && is_ans) || (cur == parent && sons > 1)) points.push_back(cur);
    }

    vector<int> find_cutpoints(vector<vector<int>>& g) {   
        tin_global = 0;
        int n = (int)g.size();
        fup.assign(n, -1);
        tin.assign(n, 0);
        points.clear();
        for (int i = 0; i < n; ++i) {
            if (tin[i] != 0) continue;
            dfs(i, i, g);
        }
        return points;
    }

}
using namespace FindAllCutPoints;
