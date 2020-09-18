//#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
//#define int ll
#define fs first
#define sd second
#define mp make_pair
#define pb push_back
#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define OUT(x) { cout << x; exit(0); }
//#define resize do_not_use_resize
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

struct pt
{
	int first, second, th;
	pt() {}
	pt(int first, int second, int th) : fs(fs), sd(sd), th(th) {}
	bool operator<(pt p)
	{
		if (fs != p.fs) return fs < p.fs;
		if (sd != p.sd) return sd < p.sd;
		return th < p.th;
	}
};

typedef vector<pt>::iterator iterp;
typedef vector<pii>::iterator iter;

const int maxn = 50 * 1000 + 5;

vi x, y;

struct node
{
	unsigned short val = 0;
	node* l = 0, *r = 0;
};
struct stree
{
	vector<node*> t;
	stree() { t.pb(new node()); }
	node*& safe_ptr(node*& ptr) { return ptr ? ptr : ptr = new node(); }
	int safe_get(node* ptr) { return ptr ? ptr->val : 0; }
	node* set(iter b, iter e, node* v, int tl = 0, int tr = maxn)
	{
		node* curv = new node(*safe_ptr(v));
		if (tl + 1 == tr)
		{
			for (auto it = b; it != e; ++it) curv->val += it->sd;
			return curv;
		}
		int mid = (tl + tr) / 2;
		iter midi = lower_bound(b, e, mp(mid, -inf));
		if (b < midi) curv->l = set(b, midi, safe_ptr(v->l), tl, mid);
		if (e > midi) curv->r = set(midi, e, safe_ptr(v->r), mid, tr);
		curv->val = safe_get(curv->l) + safe_get(curv->r);
		if (curv->val == 0)
		{
			delete curv;
			curv = nullptr;
		}
		return curv;
	}
	int get(int l, int r, node* v, int tl = 0, int tr = maxn)
	{
		if (tl == l && tr == r) return v->val;
		int mid = (tl + tr) / 2;
		int res = 0;
		if (l < mid) res += get(l, min(r, mid), safe_ptr(v->l), tl, mid);
		if (r > mid) res += get(max(l, mid), r, safe_ptr(v->r), mid, tr);
		return res;
	}
};

struct node2
{
	stree* val;
	node* ptr = nullptr;
	node2* l = 0, *r = 0;
	node2()
	{
		val = new stree();
		ptr = val->t.back();
	}
	node*& safe_ptr(node*& ptr) { return ptr ? ptr : ptr = new node(); }
	int get(int y1, int y2) { return val->get(y1, y2, safe_ptr(ptr)); }
	void set(iter b, iter e) { ptr = val->set(b, e, ptr); }
};
struct stree2
{
	vector<node2*> t;
	stree2() { t.pb(new node2()); }
	node2*& safe_ptr(node2*& ptr) { return ptr ? ptr : ptr = new node2(); }
	int safe_get(node2* ptr, int y1, int y2) { return ptr ? ptr->get(y1, y2) : 0; }
	node2* set(iterp b, iterp e, node2* v, int tl = 0, int tr = maxn)
	{
		node2* curv = new node2(*v);

		vector<pii>* kek = new vector<pii>();
		for (auto it = b; it != e; ++it) kek->pb({ it->sd, it->th });
		sort(kek->begin(), kek->end());

		if (b != e) curv->set(kek->begin(), kek->end());
		delete kek;

		if (tl + 1 == tr) return curv;
		int mid = (tl + tr) / 2;
		iterp midi = lower_bound(b, e, pt(mid, -inf, -inf));
		if (b != midi) curv->l = set(b, midi, safe_ptr(v->l), tl, mid);
		if (e != midi) curv->r = set(midi, e, safe_ptr(v->r), mid, tr);
		return curv;
	}
	int get(int l, int r, int y1, int y2, node2* v, int tl = 0, int tr = maxn)
	{
		if (tl == l && tr == r) return v->get(y1, y2);
		int mid = (tl + tr) / 2;
		int res = 0;
		if (l < mid) res += get(l, min(r, mid), y1, y2, safe_ptr(v->l), tl, mid);
		if (r > mid) res += get(max(l, mid), r, y1, y2, safe_ptr(v->r), mid, tr);
		return res;
	}
};





int32_t main()
{
	ios_base::sync_with_stdio(0);
	cout << fixed << setprecision(10);
	cin.tie(0);

#ifdef _MY
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	x.pb(-inf); x.pb(inf);
	y.pb(-inf); y.pb(inf);

	int n;
	cin >> n;
	vector<pii> pts(n);

	for (auto& it : pts)
	{
		cin >> it.fs >> it.sd;
		x.pb(it.fs);
		y.pb(it.sd);
	}

	sort(all(x));
	sort(all(y));
	sort(all(pts));
	x.resize(unique(all(x)) - begin(x));
	y.resize(unique(all(y)) - begin(y));
	pts.resize(unique(all(pts)) - begin(pts));

	for (auto& it : pts)
	{
		it.fs = int(lower_bound(all(x), it.fs) - begin(x));
		it.sd = int(lower_bound(all(y), it.sd) - begin(y));
	}

	vector<vi> forx(sz(x));
	vector<vi> fory(sz(y));
	for (auto& it : pts) forx[it.fs].pb(it.sd);
	for (auto& it : pts) fory[it.sd].pb(it.fs);
	for (auto& it : forx)
	{
		if (sz(it) == 0) continue;
		it.pb(sz(y) - 1);
		it.pb(0);
		sort(all(it));
	}
	for (auto& it : fory)
	{
		if (sz(it) == 0) continue;
		it.pb(sz(x) - 1);
		it.pb(0);
		sort(all(it));
	}


	vector<vector<pii>> eventsy(sz(y));
	vector<vector<pii>> eventsx(sz(x));
	for (int curx = 0; curx < sz(x); ++curx)
	{
		for (int i = sz(forx[curx]) - 2; i >= 0; --i)
			eventsy[forx[curx][i]].pb({ curx, forx[curx][i + 1] });
	}
	for (int cury = 0; cury < sz(y); ++cury)
	{
		for (int i = sz(fory[cury]) - 2; i >= 0; --i)
			eventsx[fory[cury][i]].pb({ cury, fory[cury][i + 1] });
	}
	for (auto& it : eventsy) sort(all(it));

	stree2 diffx;
	stree2 diffy;
	vi curxs(sz(x), 0);
	vi curys(sz(y), 0);
	vector<node2*> diffxstates;
	vector<node2*> diffystates;
	for (int cury = 0; cury < sz(y); ++cury)
	{
		map<pii, int> m;
		for (auto& it : eventsy[cury])
		{
			if (curxs[it.fs] != 0) m[{it.fs, curxs[it.fs] }]--;
			m[it]++;
		}
		vector<pt> kek;
		for (auto& it : m) if (it.sd) kek.pb({ it.fs.fs, it.fs.sd, it.sd });

		diffx.t.pb(diffx.set(all(kek), diffx.t.back()));
		diffxstates.pb(diffx.t.back());
	}
	for (int curx = 0; curx < sz(x); ++curx)
	{
		map<pii, int> m;
		for (auto& it : eventsx[curx])
		{
			if (curys[it.fs] != 0) m[{it.fs, curys[it.fs] }]--;
			m[it]++;
		}
		vector<pt> kek;
		for (auto& it : m) if (it.sd) kek.pb({ it.fs.fs, it.fs.sd, it.sd });

		diffy.t.pb(diffy.set(all(kek), diffy.t.back()));
		diffystates.pb(diffy.t.back());
	}


	int q;
	cin >> q;
	for (int i = 0; i < q; ++i)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1 = int(lower_bound(all(x), x1) - begin(x));
		y1 = int(lower_bound(all(y), y1) - begin(y));
		x2 = int(upper_bound(all(x), x2) - begin(x));
		y2 = int(upper_bound(all(y), y2) - begin(y));
		cout << diffx.get(x1, x2, y1, y2, diffxstates[y1 - 1]) << " ";
		cout << diffy.get(y1, y2, x1, x2, diffystates[x1 - 1]) << endl;
	}


#ifdef _MY
	int loop = 0;
	while (true)
	{
		for (int i = 0; i < 1000000; ++i)++loop;
		cerr << "huh" << endl;
	}
	cout << loop;
#endif

	return 0;
}