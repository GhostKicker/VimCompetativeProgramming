struct dsu {
    vector<int> p, s;
    dsu() {}
    dsu(int n) {
        p.resize(n);
        s.assign(n, 1);
        iota(all(p), 0);
    }
    int root(int v) {
        if (p[v] != v) p[v] = root(p[v]);
        return p[v];
    }
    void unite(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) return;
        if (s[b] > s[a]) swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }
};
