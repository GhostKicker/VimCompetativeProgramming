struct line{
    int64_t k, b;
    line(int64_t k = 0, int64_t b = INF) :k(k), b(b) {}
    int64_t operator[](int64_t a) { return a * k + b; }
    bool operator==(line l){ return k == l.k && b == l.b; }
    bool operator!=(line l){ return !(*this == l);}
};
struct node{
    line val = line();
    node* l = nullptr;
    node* r = nullptr;
};
node nodes[3*000*000];
int idxnode = 0;
node*& safe_ptr(node*& a){
    if (a == nullptr)
        a = nodes+(idxnode++);
    return a;
}
struct li_chao{
    static const int64_t maxn = 10 * 1000 * 1000 + 4;
    node* root;
    li_chao(){ 
        safe_ptr(root);
    }
    void set(line nl, node* v, int64_t l = 0, int64_t r = maxn){
        if (nl == line()) return;
        int64_t m = (l + r) / 2;
        bool left = nl[l] < (v->val)[l];
        bool mid = nl[m] < (v->val)[m];
        bool right = nl[r] < (v->val)[r];
        if (mid) swap(nl, v->val);
        if (r - l == 1) return;
        if (left != mid) set(nl, safe_ptr(v->l), l, m);
        if (right != mid) set(nl, safe_ptr(v->r), m, r);

    }
    int64_t get(int64_t p, node* v, int64_t l = 0, int64_t r = maxn){
        //gives minimal value in point p
        if (v->val == line()) return INF;
        int64_t m = (l + r) / 2;
        if (r - l == 1) return (v->val)[p];
        if (p < m) return min((v->val)[p], get(p, safe_ptr(v->l), l, m));
        else return min((v->val)[p], get(p, safe_ptr(v->r), m, r));
    }
};

