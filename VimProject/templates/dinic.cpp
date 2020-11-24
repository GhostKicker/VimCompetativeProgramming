struct Dinic{
    int s, t;
    int graphsize;
    struct edge { 
        int to, cap, f = 0; 
        edge() {}
        edge(int to, int cap) :to(to), cap(cap) {}
    };
    vector<vector<int>> g;
    vector<int> d, cnt;
    vector<edge> E;
    bool bfs() {
        queue<int> q;
        q.push(s);
        cnt.assign(graphsize, 0);
        d.assign(graphsize, inf);
        d[s] = 0;
        while (q.size()) {
            int v = q.front();
            if (v == t) return true;
            q.pop();
            for (auto e : g[v]) {
                if (d[E[e].to] == inf && E[e].f < E[e].cap) {
                    q.push(E[e].to);
                    d[E[e].to] = d[v] + 1;
                }
            }
        }
        return false;
    }
    int dfs(int v, int f) {
        if (v == t) return f;
        for (; cnt[v] < (int)g[v].size(); ++cnt[v]) {
            int e = g[v][cnt[v]];
            int to = E[e].to;
            if (d[to] != d[v] + 1 || E[e].f == E[e].cap) continue;
            int flow = dfs(to, min(f, E[e].cap - E[e].f));
            if (flow) {
                E[e].f += flow;
                E[e ^ 1].f -= flow;
                return flow;
            }
        }
        return 0;
    }
    
    int maxflow() {
        int f = 0;
        int ans = 0;
        while (bfs())
            while ((f = dfs(s, inf)))
                ans += f;
        return ans;
    }
    
    void add_edge(int f, int to, int cap) {
        g[f].push_back(int(E.size()));
        E.push_back(edge(to, cap));
        g[to].push_back(int(E.size()));
        E.push_back(edge(f, 0));
    }
    Dinic(){}
    Dinic(int s, int t, int graphsize):s(s), t(t), graphsize(graphsize){
        g.resize(graphsize);
    }
};
