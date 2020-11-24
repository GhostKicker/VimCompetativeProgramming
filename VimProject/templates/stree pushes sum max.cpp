struct stree {
    vector<int> t;
    vector<int> p;
    int n = 1;
    stree() {}
    stree(int nn) {
        while (n < nn) n *= 2;
        t.assign(2 * n, 0);
        p.assign(2 * n, 0);
    }
    int val(int v) { return t[v] + p[v]; }
    void push(int v) {
        t[v] += p[v];
        if (v < n) {
            p[2 * v] += p[v];
            p[2 * v + 1] += p[v];
        }
        p[v] = 0;
    }
    void upd(int v) { t[v] = max(val(2 * v), val(2 * v + 1)); }
    int get(int l, int r, int v, int tl, int tr) {
        if (tr == -1) tr = n;
        if (tl == l && tr == r) return val(v);

        push(v);
        int res = 0;
        int mid = (tl + tr) / 2;
        if (l < mid) res = max(res, get(l, min(mid, r), 2 * v, tl, mid));
        if (r > mid) res = max(res, get(max(l, mid), r, 2 * v + 1, mid, tr));
        upd(v);

        return res;
    }
    void set(int l, int r, int x, int v, int tl, int tr) {
        if (tr == -1) tr = n;
        if (tl == l && tr == r) return void(p[v] += x);

        push(v);
        int mid = (tl + tr) / 2;
        if (l < mid) set(l, min(mid, r), x, 2 * v, tl, mid);
        if (r > mid) set(max(l, mid), r, x, 2 * v + 1, mid, tr);
        upd(v);
    }
    void set(int l, int r, int x) {
        r = min(r, n);
        l = max(l, 0ll);
        set(l, r, x, 1, 0, n);
    }
    int get(int l, int r) {
        r = min(r, n);
        l = max(l, 0ll);
        return get(l, r, 1, 0, n);
    }
};
