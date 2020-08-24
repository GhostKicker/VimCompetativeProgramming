namespace FindAllBridges
{
    vector<int> bridges;
    vector<int> fup, tin;
    int tin_global = 0;
    void dfs(int cur, int parent, int edge_i, vector<vector<pair<int, int>>>& g)
    {
        tin[cur] = ++tin_global;
        fup[cur] = tin_global;
        for (int i = 0; i < g[cur].size(); i++)
        {
            int to, index;
            tie(to, index) = g[cur][i];
            if (tin[to] == 0)
            {
                dfs(to, cur, index, g);
                fup[cur] = min(fup[cur], fup[to]);
            }
            else
            {
                if (to != parent)
                    fup[cur] = min(fup[cur], tin[to]);
            }
        }
        if (fup[cur] == tin[cur] && edge_i != -1) bridges.push_back(edge_i);
    }

    vector<int> find_bridges(vector<vector<pair<int, int>>>& g)
    {   //to, index_of_edge
        tin_global = 0;
        int n = g.size();
        fup.assign(n, -1);
        tin.assign(n, 0);
        bridges.clear();
        dfs(0, -1, -1, g);
        return bridges;
    }

}