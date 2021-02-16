#ifndef _MY
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx,tune=native")
#endif
//#define _GLIBCXX_DEBUG
#include "bits/stdc++.h"
//#define int ll
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
const int maxn = 500 * 1000 + 100;
chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (double)(chrono::steady_clock::now() - cl).count() / 1e9; }
//------------------------------------------//


const ld pi = acosl(-1.0);
const ld eps = 1e-7;
bool eq(int a, int b){ return abs(a-b) < eps; }
struct pt{ 
    int x, y;
    pt(){}
    pt(int x, int y): x(x), y(y){}
};
pt operator+(pt a, pt b){ return pt(a.x+b.x, a.y+b.y); }
pt operator-(pt a, pt b){ return pt(a.x-b.x, a.y-b.y); }
int cross(pt a, pt b){ return a.x*b.y-b.x*a.y; }
int dot(pt a, pt b){ return a.x*b.x+a.y*b.y; }
ld angle(pt a, pt b){ 
    ld res = atan2l(cross(a, b), dot(a, b)); 
    if (res < 0) res += 2*pi;
    return res;
}
int norm(pt a){ return a.x*a.x+a.y*a.y; }

bool cmp(pt a, pt b){
    return angle(pt(1, 0), a) < angle(pt(1, 0), b);
}

struct stree{
    int n = 1;
    vector<int> t;
    stree(){}
    stree(int nn){
        while(n < nn) n*=2;
        t.resize(2*n, 0);
    }
    void set(int i, int x){
        t[i+=n] = x;
        for (i/=2; i; i/=2) 
            t[i] = max(t[i], x);
    }
    int get(int l, int r){
        int res = 0;
        for (l+=n, r+=n; l<=r; l/=2, r/=2){
            if (l % 2 == 1) res = max(res, t[l++]);
            if (r % 2 == 0) res = max(res, t[r--]);
        }
        return res;
    }
};

pt pts[10000];
stree tr(7000);
ld solve(vector<pt>& inp){

    sort(all(inp), cmp);
    for (auto& it : inp) cout << it.x << " " << it.y << endl;
    cout << endl;
    int n = inp.size();
    for (int i = 0; i < n; ++i) pts[i] = inp[i];
    for (int i = 0; i < n; ++i) pts[i+n] = inp[i];
    for (int i = 0; i < n; ++i) pts[i+2*n] = inp[i];

    for (int i = 0; i < 2*n; ++i) tr.set(i, norm(pts[i]));

    //for (int i = 0; i < 2*n; ++i) {
    //    cout << i << "\t";
    //    cout << tr.get(i, i) << "\t";
    //    cout << pts[i].x << "\t" << pts[i].y << endl;
    //}

    int res = 0;

    int ileft = 1;
    int iright = n+1;
    for (int i = n; i < 2*n; ++i){

        while(true){
            if (ileft == i-1) break;
            ld val = angle(pts[ileft+1], pts[i]);
            if (!eq(val, pi/3) && val < pi/3) break;
            ++ileft;
        }
        while(true){
            if (iright == i+n) break;
            ld val = angle(pts[i], pts[iright]);
            if (eq(val, pi/3) || val > pi/3) break;
            ++iright;
        }

        //int ileft, iright;
        //int l, r;
        //l = i-n+1, r = i;
        //while(l < r){
        //    int mid = (l + r) / 2;
        //    ld val = angle(pts[mid], pts[i]);
        //    if (eq(val, pi/3) || val > pi/3) l = mid+1;
        //    else r = mid;
        //}
        //ileft = r-1;

        //l = i+1, r = i+n;
        //while(l < r){
        //    int mid = (l + r) / 2;
        //    ld val = angle(pts[i], pts[mid]);
        //    if (val < pi/3) l = mid+1;
        //    else r = mid;
        //}
        //iright = r;

        //cout << "angles" << endl;
        //cout << i << "\t" << iright-n << "\t" << ileft << "\t" << sqrtl(norm(pts[i])) << endl;

        //for (int j = i+1; j < i+n; ++j){
        //    cout << angle(pts[i], pts[j]) << endl;
        //}

        int curres = norm(pts[i]);
        curres = min(curres, tr.get(iright-n, ileft));
        //cout << curres << endl;
        res = max(res, curres);
    }
    return sqrtl(res)/2;
}

int32_t main(){
    cl = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    //mt19937 rng(time(0));
    //cout << 3000 << endl;
    //for (int i = 0; i < 3000; ++i){
    //    cout << rng() % 10000 << " " << rng() % 10000 << endl;
    //}
    //return 0;

    int n;
    cin >> n;
    vector<pair<int,int>> vp(n);
    for (auto& it : vp) {
        cin >> it.first >> it.second;
    }

    sort(all(vp));
    vp.resize(unique(all(vp)) - begin(vp));

    if (vp.size() < 3){
        cout << 0.0;
        return 0;
    }

    vector<pt> inp;
    for (auto& it : vp){
        inp.push_back(pt(it.first, it.second));
    }

    ld res = 0;
    //for (auto& it : pts) cout << it.x << " " << it.y << endl;
    //cout << "---" << endl;
    for (int i = 0; i < inp.size(); ++i){
        cerr << i << endl;
        vector<pt> curpts = inp;
        curpts.erase(curpts.begin() + i);
        //cout << pts[i].x << " " << pts[i].y << endl;
        for (auto& it : curpts) it = it - inp[i];
        res = max(res, solve(curpts));
    }

    cout << res;

    return 0;
}
