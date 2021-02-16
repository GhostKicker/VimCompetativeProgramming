int sgn(const ld &a) { return (a > eps ? 1 : (a < -eps ? -1 : 0)); }

struct pt {
    ld x, y;
    pt(ld x = 0, ld y = 0) : x(x), y(y) {}
    const pt operator-(const pt &a)     const { return pt(x - a.x, y - a.y); }
    const pt operator+(const pt &a)     const { return pt(x + a.x, y + a.y); }
    const pt operator*(const ld &a)     const { return pt(x * a, y * a); }
    const pt operator/(const ld &a)     const { return pt(x / a, y / a); }
    const ld operator^(const pt &a)     const { return (x * a.y - y * a.x); }
    const ld operator*(const pt &a)     const { return (x * a.x + y * a.y); }
    const bool operator<(const pt &a)   const { return sgn(x - a.x) == -1 || (sgn(x - a.x) == 0 && sgn(y - a.y) == -1); }
    const bool operator==(const pt &a)  const { return sgn(x - a.x) == 0 && sgn(y - a.y) == 0; }
    const ld sqdist()                   const { return sq(x) + sq(y); }
    const ld dist()                     const { return sqrtl((ld)sqdist()); }
    const pt norm(const ld &a)          const { return pt(x, y) * (a / dist()); }
    const pt rotateCW(const ld &ang)    const { return pt(x * cosl(ang) - y * sinl(ang),  x * sinl(ang) + y * cosl(ang)); }
    const pt rotateCCW(const ld &ang)   const { return pt(x * cosl(ang) + y * sinl(ang), -x * sinl(ang) + y * cosl(ang)); }
};

ld ang(pt a, pt b) { return atan2l(a ^ b, a * b); }

struct line {
    ld a, b, c;
    line(pt p1, pt p2) {
        a = -(p2.y - p1.y);
        b =  (p2.x - p1.x);
        c = -(a * p1.x + b * p1.y);
        fix();
    }
    line(ld a = 1, ld b = 0, ld c = 0) : a(a), b(b), c(c) { fix(); }
    void fix() {
        ld d = sqrt(sq(a) + sq(b));
        a /= d; b /= d; c /= d;
        if (sgn(a) == -1 || (sgn(a) == 0 && sgn(b) == -1))
            a = -a, b = -b, c = -c;
    }
    const ld dist(const pt &p)        const { return fabsl(a * p.x + b * p.y + c); }
    const ld orientdist(const pt &p)  const { return a * p.x + b * p.y + c; }
    const pt proj(const pt &p)        const { return p - pt(a, b) * orientdist(p); }
    const pt symm(const pt &p)        const { return p - pt(a, b) * (orientdist(p) * 2.0); }
};

struct segment {
    pt a, b;
    segment(pt a = pt(), pt b = pt(1)) : a(a), b(b) {}
    const bool on_segment(const pt &p) const { return sgn((a - b).dist() - (a - p).dist() - (b - p).dist()) == 0; }
    const ld dist(const pt &p)         const { line l(a, b);
        return (on_segment(l.proj(p)) ? l.dist(p) : min((a - p).dist(), (b - p).dist()));
    }
};

struct circle {
    pt center;
    ld r;
    circle(pt center = pt(), ld r = 1) : center(center), r(r) {}
    const bool on_circle(const pt &p) const { return sgn((center - p).dist() - r) ==  0; }
    const bool in_circle(const pt &p) const { return sgn((center - p).dist() - r) == -1; }
    const bool out_crcle(const pt &p) const { return sgn((center - p).dist() - r) ==  1; }
    const ld dist_out_circle(const pt &a, const pt &b) {
        segment s(a, b);
        line    l(a, b);
        pt maybe_in = l.proj(center);
        if (s.on_segment(maybe_in) && in_circle(maybe_in)) {
            ld st1 = sqrtl((center - a).sqdist() - sq(r));
            ld st2 = sqrtl((center - b).sqdist() - sq(r));
            ld ang1 = PI / 2 - atan2l(r, st1);
            ld ang2 = PI / 2 - atan2l(r, st2);
            return st1 + st2 + r * (fabsl(ang(a - center, b - center)) - ang1 - ang2);
        }
        return (a - b).dist();
    }
};

struct polygon {
    vector<pt> v;
    polygon(vector<pt> v = vector<pt>()) : v(v) {}

    int det(pt a, pt b, pt c) {
        return sgn((c - b) ^ (b - a));
    }
    vector<pt> convex() {
        sort(all(v));
        vector<pt> cvx;
        pt be = v.front(), en = v.back();
        set<pt> up, dn;
        for (int i = 0; i < v.size(); ++i) {
            if (det(be, v[i], en) >= 0) up.insert(v[i]);
            if (det(be, v[i], en) <= 0) dn.insert(v[i]);
        }
        for (sit it = up.begin(); it != up.end(); ++it) {
            sit c = it;     if (*c == be) continue;
            sit b = c; --b; if (*b == be) continue;
            sit a = b; --a;
            if (det(*a, *b, *c) <= 0) { up.erase(b); --it; }
        }
        for (sit it = dn.begin(); it != dn.end(); ++it) {
            sit c = it;     if (*c == be) continue;
            sit b = c; --b; if (*b == be) continue;
            sit a = b; --a;
            if (det(*a, *b, *c) >= 0) { dn.erase(b); --it; }
        }
        for (sit it = ++up.begin(); it != up.end(); ++it) cvx.pb(*it);
        for (set<pt>::reverse_iterator it = ++dn.rbegin(); it != dn.rend(); ++it) cvx.pb(*it);
        return cvx;
    }
    ld perimeter() {
        ld ans = 0;
        for (int i = 0; i < v.size(); ++i)
            ans += (v[i] - v[(i + 1) % v.size()]).dist();
        return ans;
    }
    ld square() {
        ld ans = 0;
        for (int i = 0; i < v.size(); ++i)
            ans += v[i] ^ v[(i + 1) % v.size()];
        return fabsl(ans) / 2.0;
    }
};

struct intersections {
    static int line_line(const line &a, const line &b, pt &p) {
        pt v_a(a.a, a.b);
        pt v_b(b.a, b.b);
        if (v_a == v_b && sgn(a.c - b.c) == 0) return 2;
        if (v_a == v_b && sgn(a.c - b.c) != 0) return 0;
        ld d0 = a.a * b.b - a.b * b.a;
        p = pt(a.c * b.b - a.b * b.c, a.a * b.c - a.c * b.a) / (-d0);
        return 1;
    }
    static int line_circle(const circle &C, const line &L, pt &one, pt &two) {
        pt p = L.proj(C.center);
        if (C.on_circle(p)) { one = two = p; return 1; }
        if (C.out_crcle(p)) return 0;
        if (C.in_circle(p)) {
            pt vec = pt(-L.b, L.a) * sqrtl(sq(C.r) - (C.center - p).sqdist());
            one = p + vec;
            two = p - vec;
            return 2;
        }
        return -1;
    }
    static int circle_circle(const circle &a, const circle &b, pt &one, pt &two) {
        line l = line(-2.0 * a.center.x + 2.0 * b.center.x,
            -2.0 * a.center.y + 2.0 * b.center.y,
            sq(a.center.x) + sq(a.center.y) -
            sq(b.center.x) - sq(b.center.y) -
            sq(a.r) + sq(b.r));
        return line_circle(b, l, one, two);
    }
    static int segment_segment(const segment &a, const segment &b, pt &p) {
        bool cross = (sgn((a.a - b.a) ^ (a.b - b.a)) * sgn((a.a - b.b) ^ (a.b - b.b)) <= 0 &&
            sgn((b.a - a.a) ^ (b.b - a.a)) * sgn((b.a - a.b) ^ (b.b - a.b)) <= 0);
        ld xy = max(min(a.a.y, a.b.y), min(b.a.y, b.b.y));
        ld xx = max(min(a.a.x, a.b.x), min(b.a.x, b.b.x));
        ld ny = min(max(a.a.y, a.b.y), max(b.a.y, b.b.y));
        ld nx = min(max(a.a.x, a.b.x), max(b.a.x, b.b.x));
        bool bbox = (sgn(nx - xx) >= 0 && sgn(ny - xy) >= 0);
        if (cross && bbox) return line_line(line(a.a, a.b), line(b.a, b.b), p);
        return 0;
    }
};