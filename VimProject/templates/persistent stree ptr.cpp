namespace stree_ns
{
#ifdef _MY
    const int maxn = 8;
#endif
#ifndef _MY
    const int maxn = 1000 * 1000 + 5;
#endif

    struct stree
    {
        //changable part
        typedef int T;
        static const T neutral = inf;
        inline T func_get(T a, T b) { return min(a, b); }
        inline void func_set(T& a, T& b) { a = b; }
        //-------------

        struct node
        {
            T val = neutral;
            node* l = 0, *r = 0;
        };


        vector<node*> t;
        stree() { t.push_back(new node()); }
        node*& safe_ptr(node*& ptr) { return ptr ? ptr : ptr = new node(); }
        int safe_get(node* ptr) { return ptr ? ptr->val : neutral; }
        void build(vi& ar, node*& v, int tl = 0, int tr = maxn)
        {
            if (tl + 1 == tr) return void(v->val = ar[tl]);
            int mid = (tl + tr) / 2;
            if (tl < ar.size()) build(ar, safe_ptr(v->l), tl, mid);
            if (mid < ar.size()) build(ar, safe_ptr(v->r), mid, tr);
            v->val = func_get(safe_get(v->l), safe_get(v->r));
        }
        node* set(int i, T x, node* v, int tl = 0, int tr = maxn)
        {
            node* curv = new node(*v);
            if (i == tl && i + 1 == tr) { func_set(curv->val, x); return curv; }
            int mid = (tl + tr) / 2;
            if (i < mid) curv->l = set(i, x, safe_ptr(v->l), tl, mid);
            else curv->r = set(i, x, safe_ptr(v->r), mid, tr);
            curv->val = func_get(safe_get(curv->l), safe_get(curv->r));
            return curv;
        }
        int get(int l, int r, node* v, int tl = 0, int tr = maxn)
        {
            if (tl == l && tr == r) return v->val;
            int mid = (tl + tr) / 2;
            int res = neutral;
            if (l < mid) res = func_get(res, get(l, min(r, mid), safe_ptr(v->l), tl, mid));
            if (r > mid) res = func_get(res, get(max(l, mid), r, safe_ptr(v->r), mid, tr));
            return res;
        }
    };

    int ind = 0;
    char c[1000];
    void print(stree::node* t, int side = 0, int prside = 0)
    {
#ifdef _MY
        if (!t) return;
        c[ind] = side ^ prside ? '|' : ' ';
        ++ind;
        print(t->l, 0, side);
        c[ind] = side ? '\\' : '/';
        for (int i = 2; i <= ind; ++i) cout << ' ' << c[i] << ' ';
        cout << '[' << t->val << ']' << endl;
        print(t->r, 1, side);
        --ind;
#endif
    }
}