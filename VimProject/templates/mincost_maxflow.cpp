struct MCMF{
    int s, t;
    struct edge
    {
        int to, f = 0, cap, cost;
        edge() {}
        edge(int to, int cap, int cost) :to(to), cap(cap), cost(cost) {}
    };
     
    vector<vi> g;
    vector<edge> E;
    vi d, inq, p, pe;
    void augument()
    {
        queue<int> q;
        d.assign(t + 1, inf);
        inq.assign(t + 1, 0);
        p.assign(t + 1, -1);
        pe.assign(t + 1, -1);
        d[s] = 0;
        q.push(s);
        while (q.size())
        {
            int k = q.front();
            q.pop();
            inq[k] = 0;
            for (auto& e : g[k])
            {
                if (E[e].cap - E[e].f > 0)
                {
                    int w = E[e].cost;
                    int to = E[e].to;
                    if (d[to] > d[k] + w)
                    {
                        p[to] = k;
                        pe[to] = e;
                        d[to] = d[k] + w;
                        if (!inq[to])
                        {
                            q.push(to);
                            inq[to] = 1;
                        }
                    }
                }
            }
        }
     
     
    }
     
    int check()
    {
        if (p[t] == -1) return -1;
        int mx = inf;
        int cur = t;
        while (cur != s)
        {
            mx = min(mx, E[pe[cur]].cap - E[pe[cur]].f);
            cur = p[cur];
        }
        cur = t;
        while (cur != s)
        {
            E[pe[cur]].f += mx;
            E[pe[cur] ^ 1].f -= mx;
            cur = p[cur];
        }
        return mx * d[t];
    }
     
    int mincost_maxflow()
    {
        int res = 0;
        while (true)
        {
            augument();
            int cur = check();
            if (cur == -1) break;
            res += cur;
        }
        return res;
    }
     
    void add_edge(int f, int to, int cap, int cost)
    {
        g[f].push_back(int(E.size()));
        E.push_back(edge(to, cap, cost));
        g[to].push_back(int(E.size()));
        E.push_back(edge(f, 0, -cost));
    }

    MCMF(){}
    MCMF(int s, int t, int graphsize):s(s), t(t), graphsize(graphsize){
        g.resize(graphsize);
    }
}; 
