//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define int ll
#define xx first
#define yy second
#define pb push_back
#define all(x) begin(x), end(x)
#define OUT(x) ((cout << x), exit(0))
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const db eps = 1e-9;
const db pi = acos(-1.0);
const db dinf = 1e250;
const ll INF = (ll)(2e18);
const int inf = (int)(1e9 + 7);
//------------------------------------------//

map<int, vector<pii>> m;

const int maxn = inf;

struct node
{
    node* l = nullptr, * r = nullptr;
    int32_t mx = 0, p = 0;
};
node*& safe_ptr(node*& ptr) { return ptr ? ptr : ptr = new node(); }
int safe_get(node*& ptr) { return ptr ? ptr->mx + ptr->p : 0; }
struct stree
{
    node* t;
    stree() { t = new node(); }


    void push(node* v, int tl, int tr)
    {
        if (tl == tr) return;
        v->mx += v->p;
        if (tl + 1 != tr)
        {
            safe_ptr(v->l)->p += v->p;
            safe_ptr(v->r)->p += v->p;
        }
        v->p = 0;
    }

    void set(int l, int r, int x, node* v, int tl = 0, int tr = maxn)
    {
        if (tl == l && tr == r) return void(v->p += x);

        push(v, tl, tr);

        int mid = (tl + tr) / 2;
        if (l < mid) set(l, min(mid, r), x, safe_ptr(v->l), tl, mid);
        if (r > mid) set(max(mid, l), r, x, safe_ptr(v->r), mid, tr);

        push(safe_ptr(v->l), tl, mid);
        push(safe_ptr(v->r), mid, tr);
        v->mx = max(safe_get(v->l), safe_get(v->r));
    }
    int get(int l, int r, node* v, int tl = 0, int tr = maxn)
    {
        push(v, l, r);
        if (l == tl && r == tr) return v->mx;
        int res = -INF;
        int mid = (tl + tr) / 2;
        if (l < mid) res = max(res, get(l, min(mid, r), safe_ptr(v->l), tl, mid));
        if (r > mid) res = max(res, get(max(mid, l), r, safe_ptr(v->r), mid, tr));
        return res;
    }

    int get_max_ind(node* v, int tl = 0, int tr = maxn)
    {
        push(v, tl, tr);

        if (tl + 1 == tr) return tl;
        int mid = (tl + tr) / 2;
        if (safe_get(v->l) == v->mx) return get_max_ind(safe_ptr(v->l), tl, mid);
        else return get_max_ind(safe_ptr(v->r), mid, tr);
    }

};

int ind = 0;
char c[1000];
void print(node* t, int side = 0, int prside = 0)
{
#ifdef _MY
    if (!t) return;
    c[ind] = side ^ prside ? '|' : ' ';
    ++ind;
    print(t->l, 0, side);
    c[ind] = side ? '\\' : '/';
    for (int i = 2; i <= ind; ++i) cout << ' ' << c[i] << ' ';
    cout << '[' << t->mx << "," << t->p << ']' << endl;
    print(t->r, 1, side);
    --ind;
#endif
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cout << fixed << setprecision(10);
    cin.tie(0);

#ifdef _MY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n;
    cin >> n;

    set<pii> pts;

    int res = 0;
    pii resp;

    m[0].pb({ 0,0 });
    for (int i = 0; i < n; ++i)
    {
        int x, y, c;
        cin >> x >> y >> c;
        m[min(x, y)].pb({ max(x,y), c });
        pts.insert({ x,y });
        
    }

    for (int i = 0; ; ++i)
    {
        if (!pts.count({ i,i }))
        {
            resp = { i,i };
            break;
        }
    }



    stree tr;


    set<int> s;
    for (auto& it : m)
    {
        s.insert(it.xx);
        for (auto& itt : it.yy)
            s.insert(itt.xx);
    }
    auto its1 = s.begin();
    auto its2 = its1; ++its2;




    for (; its1 != s.end(); ++its1, its2 == s.end() ? its2 : ++its2)
    {
        if (its2 != s.end())
            tr.set(*its1, *its2, -*its1, tr.t);
        else
            tr.set(*its1, maxn, -*its1, tr.t);
    }
    //print(tr.t);

    for (auto& it : m)
    {
        for (auto& itt : it.yy)
            tr.set(itt.xx, maxn, itt.yy, tr.t);
        
    }


    

    auto it1 = m.begin();
    auto it2 = it1; ++it2;

    for (; it2 != m.end(); ++it1, ++it2)
    {
        //print(tr.t); cout << endl;
        if (safe_get(tr.t) > res)
        {
            res = safe_get(tr.t);
            resp = { it1->xx, tr.get_max_ind(tr.t) };
        }
        //print(tr.t); cout << endl;
        for (auto& itt : it1->yy) tr.set(itt.xx, maxn, -itt.yy, tr.t);
        tr.set(it1->xx, maxn, it2->xx - it1->xx, tr.t);
        tr.set(it1->xx, it2->xx, -INF, tr.t);
    }

    cout << res << endl;
    cout << resp.xx << " " << resp.xx << " " << resp.yy << " " << resp.yy;


    return 0;
}