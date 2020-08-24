
/*
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
};
using namespace GEOMA_INT;
*/

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
};
using namespace GEOMA_REAL;

