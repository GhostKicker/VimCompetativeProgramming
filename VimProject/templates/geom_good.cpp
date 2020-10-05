
namespace GEOMA_INT{
    typedef long long ll;
    bool eq(ll a, ll b){return a == b;}
    struct pt{
        ll x, y;
        pt(){}
        pt(ll x, ll y):x(x), y(y){}
        bool operator<(pt a){return eq(x, a.x)? y < a.y : x < a.x;}
        pt operator-(){return pt(-x, -y);}
        pt operator+(pt b){return pt(x + b.x, y + b.y);}
        pt operator-(pt b){return pt(x - b.x, y - b.y);}
        pt operator*(ll m){return pt(x*m, y*m);}
        pt& operator+=(pt b){return *this = *this + b;}
        pt& operator-=(pt b){return *this = *this - b;}
        pt& operator*=(ll m){return *this = *this * m;}
    };
    pt operator*(ll a, pt b){return pt(a*b.x, a*b.y);}
    ostream& operator<<(ostream& str, pt p){ 
        return str << "[" << p.x << ", " << p.y << "]";
    }
    bool eq(pt a, pt b){return eq(a.x, b.x) && eq(a.y, b.y);}
    ll dot  (pt a, pt b){return a.x*b.x + a.y*b.y;}
    ll cross(pt a, pt b){
        ll res = 0;
        res += a.y * b.x;
        res -= a.x * b.y;
        return res;
    }
    ll dist2(pt a, pt b = pt(0, 0)){
        ll res = 0;
        res += (a.x - b.x) * (a.x - b.x);
        res += (a.y - b.y) * (a.y - b.y);
        return res;
    }

    //given vector of points of polygon
    //returns 2 times area of that polygon
    ll polygon_area_x2(vector<pt> v){
        ll res = 0;
        for (int i = 0; i < (int)v.size(); ++i){
            res += cross(v[i], v[(i+1)%(int)v.size()]);
        }
        return abs(res);
    }
    struct circle{
        pt c;
        ll r;
        circle(){}
        circle(pt c, ll r):c(c), r(r){}
    };
    bool is_inside(pt p, circle c){ return dist2(p, c.c) < c.r*c.r; }
    bool on_surface(pt p, circle c){ return dist2(p, c.c) == c.r*c.r; }

    vector<pt> convex_hull(vector<pt> pts){
        sort(all(pts));
        pt pl = pts[0];
        for (int i = (int)pts.size() - 1; i >= 0; --i){
            pts[i] = pts[i] - pts[0];
        }
        sort(pts.begin() + 1, pts.end(), [](pt a, pt b){
                    if (cross(a, b) > 0) return false;
                    if (cross(a, b) < 0) return true;
                    return dist2(a) < dist2(b);
                });
        vector<pt> order;
        order.push_back(pts[0]);
        for (int i = 1; i < (int)pts.size(); ++i){
            while(order.size() >= 2){
                pt arg1 = pts[i] - order.back();
                pt arg2 = order.back() - order[(int)order.size() - 2];
                if (cross(arg1, arg2) > 0) break;
                order.pop_back();
            }
            order.push_back(pts[i]);
        }
        for (auto& it : order) it = it + pl;
        return order;

    }
};
using namespace GEOMA_INT;

/*
namespace GEOMA_REAL{
    typedef long double ld;
    const ld eps = 1e-6;
    const ld pi = acos(-1.0);
    bool eq(ld a, ld b){return abs(a-b) < eps;}
    
    struct pt{
        ld x, y;
        pt(){}
        pt(ld x, ld y):x(x),y(y){}
        bool operator<(pt a){return eq(x, a.x)? y < a.y : x < a.x;}
        pt operator-(){return pt(-x, -y);}
        pt operator+(pt b){return pt(x + b.x, y + b.y);}
        pt operator-(pt b){return pt(x - b.x, y - b.y);}
        pt operator*(ld m){return pt(x*m, y*m);}
        pt operator/(ld m){assert(!eq(m, 0.0)); return pt(x/m, y/m);}
        pt& operator+=(pt b){return *this = *this + b;}
        pt& operator-=(pt b){return *this = *this - b;}
        pt& operator*=(ld m){return *this = *this * m;}
        pt& operator/=(ld m){return *this = *this / m;}
    };
    pt operator*(ld a, pt b){return pt(a*b.x, a*b.y);}
    ostream& operator<<(ostream& str, pt p){ 
        return str << "[" << p.x << ", " << p.y << "]";
    }

    bool eq(pt a, pt b){return eq(a.x, b.x) && eq(a.y, b.y);}
    ld dot  (pt a, pt b){return a.x*b.x + a.y*b.y;}
    ld cross(pt a, pt b){
        ld res = 0;
        res += a.y * b.x;
        res -= a.x * b.y;
        return res;
    }
    ld dist2(pt a, pt b = pt(0, 0)){
        ld res = 0;
        res += (a.x - b.x) * (a.x - b.x);
        res += (a.y - b.y) * (a.y - b.y);
        return res;
    }
    ld dist(pt a, pt b = pt(0, 0)){return sqrt(dist2(a, b));}
    
    //given vector of points of polygon
    //returns area of that polygon
    ld polygon_area(vector<pt> v){
        ld res = 0;
        for (int i = 0; i < (int)v.size(); ++i){
            res += cross(v[i], v[(i+1)%(int)v.size()]);
        }
        return abs(res) / 2;
    }

    ld angle(pt p){return atan2(p.y, p.x);}
    pt rotate(pt p, ld a){
        pt res;
        res.x = cos(a)*p.x - sin(a)*p.y;
        res.y = sin(a)*p.x + cos(a)*p.y;
        return res;
    }

    struct circle{
        pt c; ld r;
        circle(){}
        circle(pt c, ld r):c(c),r(r){}
    };
    
    //returns whether point is strictly inside the circle
    bool is_inside(pt p, circle c){
        ld d = dist2(p, c.c);
        if (eq(d, c.r*c.r)) return false;
        if (d > c.r*c.r) return false;
        return true;
    }


    //returns whether point is strictly on surface of circle
    bool on_surface(pt p, circle c){return eq(dist2(p, c.c), c.r*c.r);}


    //returns points on surface of circle that
    //are in lines tangent to that circle
    //in counterclockwise order
    pair<pt, pt> tangent_points(pt p, circle c){
        ld hsqr = dist2(p, c.c);
        assert(!eq(hsqr, c.r*c.r));
        assert(hsqr > c.r*c.r);
        ld bsqr = hsqr - c.r*c.r;
        ld ang = acos(sqrt(bsqr / hsqr));
        pt cur(sqrt(bsqr), 0);
        pair<pt, pt> res;
        res.first  = rotate(cur, angle(c.c - p) - ang) + p;
        res.second = rotate(cur, angle(c.c - p) + ang) + p;
        return res;
    }

    typedef pair<pt, pt> seg;

    struct line {
        //ax + by + c = 0;
        ld a = 0;
        ld b = 0;
        ld c = 0;
        line() {}
        line(ld a, ld b, ld c): a(a), b(b), c(c) {}
        ld inp(pt p) { return a*p.x + b*p.y + c; }
        line(pt p1, pt p2) {
            a = p2.y - p1.y;
            b = p1.x - p2.x;
            c = -(a*p1.x + b*p1.y);
        }
    };

    int sign(ld a){
        if (fabs(a) < eps) return 0;
        return (a < 0 ? -1 : 1);
    }

    seg bounding_rectangle(seg s) {
        seg res;
        res.first.x = min(s.first.x, s.second.x);
        res.first.y = min(s.first.y, s.second.y);
        res.second.x = max(s.first.x, s.second.x);
        res.second.y = max(s.first.y, s.second.y);
        return res;
    }
    
    bool segment_intersection(seg s1, seg s2) {
        seg br1 = bounding_rectangle(s1);
        seg br2 = bounding_rectangle(s2);
        if ((br1.second.x - br2.first.x) > -eps &&
            (br2.second.x - br1.first.x) > -eps &&
            (br1.second.y - br2.first.y) > -eps &&
            (br2.second.y - br1.first.y) > -eps) {
            if (sign(cross(s2.first - s1.first, s1.second - s1.first))*sign(cross(s2.second - s1.first, s1.second - s1.first)) < 1)
                if (sign(cross(s1.first - s2.first, s2.second - s2.first))*sign(cross(s1.second - s2.first, s2.second - s2.first)) < 1)
                    return true;
        }
        return false;
    }

    pt cross_point(line l1, line l2) {
        if (abs(l1.a) > eps) swap(l1, l2);
        ld y = -(l1.c - l2.c*l1.a / l2.a) / (l1.b - l2.b*l1.a / l2.a);
        if (abs(l2.b) > eps) swap(l1, l2);
        ld x = -(l2.c - l1.c*l2.b / l1.b) / (l2.a - l1.a*l2.b / l1.b);
        return pt(x, y);
    }
    pair<bool, pt> intersection_point(seg s1, seg s2){
        //first is true if segments intersect
        //if first is true then second is point of intersection
        pair<bool, pt> res;
        res.first = segment_intersection(s1, s2);
        if (res.first == false) return res;
        
        res.second = cross_point(line(s1.first, s1.second), line(s2.first, s2.second));
        return res;
    }
};
using namespace GEOMA_REAL;
*/
