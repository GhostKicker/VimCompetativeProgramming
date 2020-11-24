struct line{
    int64_t k, b;
    line(int64_t k = 0, int64_t b = INF) :k(k), b(b) {}
    int64_t operator[](int64_t a) { return a * k + b; }
};
struct node{
    line val = line();
    node* l = nullptr;
    node* r = nullptr;
};
node nodes[3'000'000];
int idxnode = 0;
node*& safe_ptr(node*& a){
    if (a == nullptr)
        a = nodes+(idxnode++);
    return a;
}
struct li_chao{
    static const int64_t maxn = 100 * 1000 + 4;
    vector<int64_t> x;
    node* root;
    int64_t n = 1;
    li_chao() {}
    li_chao(vector<int64_t>& xx){ 
        //unordered array of all xs
        x = xx;
        x.push_back(inf);
        sort(all(x));
        x.resize(unique(all(x)) - begin(x));
        safe_ptr(root);
    }
    void set(line nl, node* v, int64_t l = 0, int64_t r = maxn){
        r = min(r, (int64_t)x.size() - 1);
        int64_t m = (l + r) / 2;
        bool left = nl[x[l]] < (v->val)[x[l]];
        bool mid = nl[x[m]] < (v->val)[x[m]];
        bool right = nl[x[r]] < (v->val)[x[r]];
        if (mid) swap(nl, v->val);
        if (r - l == 1) return;
        if (left != mid) set(nl, safe_ptr(v->l), l, m);
        if (right != mid) set(nl, safe_ptr(v->r), m, r);

    }
    int64_t get(int64_t p, node* v, int64_t l = 0, int64_t r = maxn){
        //gives minimal value
        r = min(r, (int64_t)x.size() - 1);
        int64_t m = (l + r) / 2;
        if (r - l == 1) return (v->val)[x[p]];
        if (p < m) return min((v->val)[x[p]], get(p, safe_ptr(v->l), l, m));
        else return min((v->val)[x[p]], get(p, safe_ptr(v->r), m, r));
    }
};

