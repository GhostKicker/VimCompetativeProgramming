struct LCA
{
    int root = 0;
    vi dep;
    vector<vi> p;
    void dfs(int v, int par, int curd, vector<vi>& g)
    {
        dep[v] = curd;
        p[v][0] = par;

        for (int i = 1; i < 20; ++i)
        {
            p[v][i] = p[p[v][i - 1]][i - 1];
        }

        for (auto& it : g[v])
        {
            if (it == par) continue;
            dfs(it, v, curd + 1, g);
        }
    }
    void init(vector<vi>& g)
    {
        dep.resize(g.size(), -1);
        p.resize(g.size(), vi(20, -1));
        dfs(root, root, 0, g);
    }

    int parent(int v, int h)
    {
        for (int i = 0; i < 20; ++i)
        {
            if (h & (1 << i))
                v = p[v][i];
        }
        return v;
    }

    int lca(int a, int b)
    {
        if (dep[a] < dep[b]) swap(a, b);
        a = parent(a, dep[a] - dep[b]);
        if (a == b) return a;

        for (int i = 19; i >= 0; --i)
        {
            if (p[a][i] != p[b][i])
            {
                a = p[a][i];
                b = p[b][i];
            }
        }
        return p[a][0];
    }
    LCA() {}
    LCA(vector<vi>& g, int rt = 0):root(rt) { init(g); }
};