struct dsu {
    vector<int> p, s, B;
    dsu() {}
    dsu(int n) {
        p.resize(n);
        s.assign(n, 1);
        iota(all(p), 0);
    }
    int root(int v) { return p[v] == v ? v : root(p[v]); }
    void unite(int a, int b) {
        a = root(a);
        b = root(b);
        if (a == b) { B.push_back(-1); return; }
        if (s[a] < s[b]) swap(a, b);
        s[a] += s[b];
        p[b] = a;
        B.push_back(b);
    }
    void rollback() {
        int b = B.back();
        B.pop_back();
		if (b == -1) return;
        s[p[b]] -= s[b];
        p[b] = b;
    }
};
