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
    void push(int v, int tl, int tr) {
        t[v] += p[v] * (tr - tl);
        if (v < n) {
            p[v + v] += p[v];
            p[v + v + 1] += p[v];
        }
        p[v] = 0;
    }
    void set(int l, int r, int x, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n;
        if (l >= r) return;
        push(v, tl, tr);
        if (l == tl && r == tr) return void(p[v] += x);
        int mid = (tl + tr) / 2;
        if (l < mid) set(l, min(r, mid), x, v + v, tl, mid);
        if (r > mid) set(max(l, mid), r, x, v + v + 1, mid, tr);
        if (v < n) {
            push(v + v, tl, mid);
            push(v + v + 1, mid, tr);
        }
        t[v] = t[v + v] + t[v + v + 1];
    }
    int get(int l, int r, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n;
        if (l >= r) return 0;
        push(v, tl, tr);
        if (l == tl && r == tr) return t[v];
        int mid = (tl + tr) / 2;
        int res = 0;
        if (l < mid) res += get(l, min(r, mid), v + v, tl, mid);
        if (r > mid) res += get(max(l, mid), r, v + v + 1, mid, tr);
        return res;
    }
};