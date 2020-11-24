namespace my_treap {
    mt19937 rng(0);
    inline bool check(int l, int r) { return rng() % (l + r) < l; }

    struct Node {
        Node *l, *r;
        int val;
        int cnt = 1;
        Node() {}
        Node(int val) :val(val) { l = r = 0; }
    };
    typedef Node* treap;

    inline int cnt(treap t) { return t ? t->cnt : 0; }
    inline void upd(treap& t) { if (t) t->cnt = cnt(t->l) + 1 + cnt(t->r); }
    inline void push(treap& t) {}

    void split(treap& tl, treap& tr, treap t, int key)
    {
        push(t);
        if (!t) return void(tl = tr = nullptr);
        if (cnt(t->l) < key) {
            split(t->r, tr, t->r, key - cnt(t->l) - 1);
            upd(tl = t);
        }
        else {
            split(tl, t->l, t->l, key);
            upd(tr = t);
        }
    }
    void merge(treap& t, treap tl, treap tr) {
        push(tl); push(tr);
        if (!tl || !tr) { t = tl ? tl : tr; }
        else if (check(cnt(tl), cnt(tr))) {
            merge(tl->r, tl->r, tr);
            t = tl;
        }
        else {
            merge(tr->l, tl, tr->l);
            t = tr;
        }
        upd(t);
    }
    int at(treap& t, int i) {
        treap t1, t2, t3;
        split(t1, t2, t, i);
        split(t2, t3, t2, 1);
        int res = t2->val;
        merge(t, t1, t2);
        merge(t, t, t3);
        return res;
    }
    treap build(vi& ar) {
        treap t = nullptr;
        for (auto& it : ar) merge(t, t, new Node(it));
        return t;
    }

    int ind = 0;
    char c[1000];
    void print(Node* t, int side = 0, int prside = 0)
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
using namespace my_treap;
