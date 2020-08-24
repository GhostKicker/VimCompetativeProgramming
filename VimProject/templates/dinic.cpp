int s, t;
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
    cnt.assign(t + 1, 0);
    d.assign(t + 1, inf);
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
    for (; cnt[v] < g[v].size(); ++cnt[v]) {
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

int Dinic() {
    int f = 0;
    int ans = 0;
    while (bfs())
        while (f = dfs(s, inf))
            ans += f;
    return ans;
}

void add_edge(int f, int to, int cap) {
    g[f].push_back(int(E.size()));
    E.push_back(edge(to, cap));
    g[to].push_back(int(E.size()));
    E.push_back(edge(f, 0));
}
