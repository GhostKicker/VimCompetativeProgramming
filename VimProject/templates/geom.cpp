#include <bits/stdc++.h>
//#define int int64_t
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << x << endl)
#define OUT(x) ((cout << x), exit(0))
using namespace std;
typedef long double db;
const db eps = 1e-9;
const db pi = acos(-1.0);
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(1e9 + 7);
//------------------------------------------//

bool eq(db a, db b) { return abs(a - b) < eps; }
struct pt {
    db x, y;
    pt() {}
    pt(db x, db y) :x(x), y(y) {}
    bool operator<(pt a){return eq(x, a.x)? y < a.y : x < a.x;}
    pt operator+(pt b) { return pt(x + b.x, y + b.y); }
    pt operator-(pt b) { return pt(x - b.x, y - b.y); }
    pt operator*(db d) { return pt(x * d, y * d); }
    pt operator/(db d) { return pt(x / d, y / d); }
    pt& operator+=(pt b) { return *this = *this + b; }
    pt& operator-=(pt b) { return *this = *this + b; }
    pt& operator*=(db d) { return *this = *this * d; }
    pt& operator/=(db d) { return *this = *this / d; }
};
pt operator*(db d, pt p) { return pt(p.x * d, p.y * d); }
ostream& operator<<(ostream& os, pt p) { return os << '[' << p.x << ", " << p.y << ']'; }
istream& operator>>(istream& is, pt& p) { return is >> p.x >> p.y; }

bool eq(pt a, pt b) { return eq(a.x, b.x) && eq(a.y, b.y); }
db dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
db cross(pt a, pt b) { return a.y * b.x - a.x * b.y; }
db dist2(pt a, pt b = pt(0, 0)) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }
db angle(pt a, pt b = pt(1, 0)) { return atan2(cross(a, b), dot(a, b)); }

db polygon_area(vector<pt> polygon) {
    db res = 0;
    for (int i = 0; i < (int)polygon.size(); ++i)
        res += cross(polygon[i], polygon[(i + 1) % int(polygon.size())]);
    return abs(res / 2);
}

struct line {
    db a, b, c;
    line() {}
    line(db a, db b, db c) :a(a), b(b), c(c) {}
    line(pt p1, pt p2) :a(p1.y - p2.y), b(p2.x - p1.x), c(-a*p1.x - b*p1.y) {}
    db at(pt p) { return a * p.x + b * p.y + c; }
};
line normal(line l) {
    db mult = 1.0 / sqrt(l.a * l.a + l.b * l.b);
    return line(l.a * mult, l.b * mult, l.c * mult);
}
line bisector_line(pt a, pt b, pt c) {
    //line of angle abc
    pt v1 = (a - b); v1 /= sqrt(dist2(v1));
    pt v2 = (c - b); v2 /= sqrt(dist2(v2));
    return line(b, b + v1 + v2);
}
db dist(pt p, line l) { return abs(l.at(p) / sqrt(dist2(pt(l.a, l.b)))); }
db dist(line l, pt p) { return dist(p, l); }


struct beam {
    pt st, fn;
    line l;
    beam() {}
    beam(pt p1, pt p2) :st(p1), fn(p2), l(p1, p2) {}
};
db dist(pt p, beam b) {
    if (dot(p - b.st, b.fn - b.st) < 0) return sqrt(dist2(p, b.st));
    return dist(p, b.l);
}
db dist(beam b, pt p) { return dist(p, b); }

struct segment {
    pt st, fn;
    line l;
    segment() {}
    segment(pt pt1, pt pt2) :st(pt1), fn(pt2), l(pt1, pt2) {}
};
db dist(pt p, segment s) {
    if (dot(p - s.st, s.fn - s.st) < 0) return sqrt(dist2(p, s.st));
    if (dot(p - s.fn, s.st - s.fn) < 0) return sqrt(dist2(p, s.fn));
    return dist(p, s.l);
}
db dist(segment b, pt p) { return dist(p, b); }

segment bounding_rectangle(segment s){
    segment res;
    res.st.x = min(s.st.x, s.fn.x);
    res.st.y = min(s.st.y, s.fn.y);
    res.fn.x = max(s.st.x, s.fn.x);
    res.fn.y = max(s.st.y, s.fn.y);
    return res;
}
bool intersect(segment s1, segment s2)
{
    segment br1 = bounding_rectangle(s1);
    segment br2 = bounding_rectangle(s2);
    if ((br1.fn.x - br2.st.x) > -eps &&
        (br2.fn.x - br1.st.x) > -eps &&
        (br1.fn.y - br2.st.y) > -eps &&
        (br2.fn.y - br1.st.y) > -eps)
    {
        db c1 = cross(s2.st - s1.st, s1.fn - s1.st) * cross(s2.fn - s1.st, s1.fn - s1.st);
        db c2 = cross(s1.st - s2.st, s2.fn - s2.st) * cross(s1.fn - s2.st, s2.fn - s2.st);
        if (c1 > -eps || c2 > -eps) return false;
        return true;
    }
    return false;
}
db dist(segment s1, segment s2) {
    if (intersect(s1,s2)) return 0.0;
    db res = dist(s1.st, s2);
    res = min(res, dist(s1.fn, s2));
    res = min(res, dist(s2.st, s1));
    res = min(res, dist(s2.fn, s1));
    return res;
}
pt cross_point(segment a, segment b) {
    pt l = a.st;
    pt r = a.fn;
    for (int i = 0; i < 100; ++i) {
        if (eq(l, r)) break;
        pt mid1 = (2 * l + r) / 3;
        pt mid2 = (l + 2 * r) / 3;
        if (dist(mid1, b) < dist(mid2, b)) r = mid2;
        else l = mid1;
    }
    return r;
}
pt cross_point(line a, line b){
    pt res;
    res.x = (a.c * b.b - b.c * a.b) / (a.a * b.b - b.a * a.b);
    res.y = (a.a * b.c - b.a * a.c) / (a.a * b.b - b.a * a.b);
    return res;
}



int32_t main() {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifndef _MY
    freopen("line1.in", "r", stdin);
    freopen("line1.out", "w", stdout);
#endif

    pt a, b;
    cin >> a >> b;
    line l(a, b);
    cout << l.a << " " << l.b << " " << l.c;



    return 0;
}
