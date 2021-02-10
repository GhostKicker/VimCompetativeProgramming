struct line {
    int64_t k, b;
    line(int64_t k = 0, int64_t b = INF) :k(k), b(b) {}
    int64_t operator[](int64_t a) { return a * k + b; }
    bool operator==(line l){ return k == l.k && b == l.b; }
    bool operator!=(line l){ return !(*this == l); }
};
struct li_chao {
    static const int64_t maxn = 100 * 1000 + 4;
    vector<int64_t> x;
    vector<line> tr;
    int64_t n = 1;
    li_chao() {}
    li_chao(vector<int64_t>& xx) { 
        //unordered array of all xs
        x = xx;
        x.push_back(INF);
        sort(all(x));
        x.resize(unique(all(x)) - begin(x));
        tr.assign(4 * maxn, line());
    }
    void set(line nl, int64_t v = 1, int64_t l = 0, int64_t r = maxn) {
        r = min(r, (int64_t)x.size() - 1);
        if (nl == line()) return;
        int64_t m = (l + r) / 2;
        bool left = nl[x[l]] < tr[v][x[l]];
        bool mid = nl[x[m]] < tr[v][x[m]];
        bool right = nl[x[r]] < tr[v][x[r]];
        if (mid) swap(nl, tr[v]);
        if (r - l == 1) return;
        if (left != mid) set(nl, v + v, l, m);
        if (right != mid) set(nl, v + v + 1, m, r);

    }
    int64_t get(int64_t p, int64_t v = 1, int64_t l = 0, int64_t r = maxn) {
        //gives minimal value in point p
        r = min(r, (int64_t)x.size() - 1);
        if (tr[v] == line()) return tr[v][p];
        int64_t m = (l + r) / 2;
        if (r - l == 1) return tr[v][p];
        if (p < m) return min(tr[v][p], get(p, v + v, l, m));
        else return min(tr[v][p], get(p, v + v + 1, m, r));
    }
};
