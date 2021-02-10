// set a = min(a,b)
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; } 
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

using T = double; // or long long
const T eps = 1e-9; // might want to change
struct pt{
    T x = 0; T y = 0;
    pt(){}
    pt(T nx, T ny):x(nx),y(ny){}
};
using Line = pair<pt,pt>;
int sgn(T a) { return (a>eps)-(a<-eps); }
T sq(T a) { return a*a; }

#define f first
#define s second
bool eq(const pt& a, const pt& b) { return sgn(a.x-b.x) == 0 && sgn(a.y-b.y) == 0; } 
T norm(const pt& p) { return sq(p.x)+sq(p.y); } 
T abs(const pt& p) { return sqrt(norm(p)); } //length of vector
T arg(const pt& p) { return atan2(p.y,p.x); } //angle
pt conj(const pt& p) { return pt(p.x,-p.y); } //complex conjugate
pt perp(const pt& p) { return pt(-p.y,p.x); } //perpendicular
pt dir(T ang) { return pt(cos(ang),sin(ang)); } //vector directing at angle

pt operator-(const pt& l) { return pt(-l.x,-l.y); }
pt operator+(const pt& l, const pt& r) { return pt(l.x+r.x,l.y+r.y); }
pt operator-(const pt& l, const pt& r) { return pt(l.x-r.x,l.y-r.y); }
pt operator*(const pt& l, const T& r) { return pt(l.x*r,l.y*r); }
pt operator*(const T& l, const pt& r) { return r*l; }
pt operator/(const pt& l, const T& r) { return pt(l.x/r,l.y/r); }
pt operator*(const pt& l, const pt& r) { return pt(l.x*r.x-l.y*r.y,l.y*r.x+l.x*r.y); }
pt operator/(const pt& l, const pt& r) { return l*conj(r)/norm(r); }
pt& operator+=(pt& l, const pt& r) { return l = l+r; }
pt& operator-=(pt& l, const pt& r) { return l = l-r; }
pt& operator*=(pt& l, const T& r) { return l = l*r; }
pt& operator/=(pt& l, const T& r) { return l = l/r; }
pt& operator*=(pt& l, const pt& r) { return l = l*r; }
pt& operator/=(pt& l, const pt& r) { return l = l/r; }

pt unit(const pt& p) { return p/abs(p); }
T dot(const pt& a, const pt& b) { return a.x*b.x+a.y*b.y; }
T cross(const pt& a, const pt& b) { return a.x*b.y-a.y*b.x; }
T cross(const pt& p, const pt& a, const pt& b) { return cross(a-p,b-p); }
pt reflect(const pt& p, const Line& l) { 
    //on opposite side of line
	pt a = l.first, d = l.second-l.first;
	return a+conj((p-a)/d)*d; 
}
pt foot(const pt& p, const Line& l) { 
    //where it lands on line
	return (p+reflect(p,l))/(T)2; 
}
bool p_on_seg(const pt& p, const Line& l) {
    //is pt on segment
	return sgn(cross(l.first,l.second,p)) == 0 && sgn(dot(p-l.first,p-l.second)) <= 0; 
}

using Half = array<T,3>; // half-plane
pt hp_point(const Half& h) { return {h[0],h[1]}; } // direction of half-plane
pt isect(const Half& h0, const Half& h1) { // Cramer's rule to intersect half-planes
	array<T,3> vals;
	for(int i=-1;i<2;++i) {
		int x = (i == 0 ? 2 : 0), y = (i == 1 ? 2 : 1);
		vals[1+i] = h0[x]*h1[y]-h0[y]*h1[x];
	}
	assert(vals[0] != 0); return {vals[1]/vals[0],vals[2]/vals[0]};
}
T eval(const Half& h, T x) { assert(h[1] != 0); // evaluate half-plane at x-coordinate
	return (h[2]-h[0]*x)/h[1]; }
T x_isect(const Half& h0, const Half& h1) { return isect(h0,h1).x; } // x-coordinate of intersection

vector<Half> construct_lower(pt x, vector<Half> planes) { // similar to convex hull (by duality)
	sort(all(planes),[](const Half& a, const Half& b) {
		return cross(hp_point(a),hp_point(b)) > 0; });
	vector<Half> res{{1,0,x.x}}; // >= x.x
	planes.push_back({-1,0,-x.y}); // <= x.y
	auto lst_x = [&](Half a, Half b) {
		if (cross(hp_point(a),hp_point(b)) == 0) // parallel half-planes, remove lower one
			return a[2]/a[1] <= b[2]/b[1] ? x.x : x.y;
		return x_isect(a,b);
	};
	for (auto& t : planes) {
		while ((int)res.size() > 1 && lst_x(res.back(),t) <= lst_x(end(res)[-2],res.back()))
			res.pop_back();
		res.push_back(t);
	}
	return res;
}

T isect_area(vector<Half> planes) {
	const T BIG = 1e9; pt x{-BIG,BIG};
	planes.push_back({0,1,-BIG}); // y >= -BIG
	planes.push_back({0,-1,-BIG}); // -y >= -BIG
	vector<Half> upper, lower;
	for (auto& t : planes) {
		if (t[1] == 0) { // vertical line
			T quo = t[2]/t[0];
			if (t[0] > 0) ckmax(x.x,quo);
			else ckmin(x.y,quo); // -x >=
		} else if (t[1] > 0) lower.push_back(t);
		else upper.push_back(t);
	}
	if (x.x >= x.y) return 0;
	lower = construct_lower(x,lower);

	for (auto& t : upper) t[0] *= -1, t[1] *= -1; 
	upper = construct_lower({-x.y,-x.x},upper);
	for (auto&t:upper) t[0] *= -1, t[1] *= -1;
	reverse(all(upper));
	int iu = 1, il = 1;
	T lst = x.x, lst_dif = eval(upper[1],lst)-eval(lower[1],lst);
	T ans = 0;
	while (iu < (int)upper.size()-1 && il < (int)lower.size()-1) { 
        // sweep vertical line through lower and upper hulls
		T nex_upper = x_isect(upper[iu],upper[iu+1]);
		T nex_lower = x_isect(lower[il],lower[il+1]);
		T nex = min(nex_upper,nex_lower);
		T nex_dif = eval(upper[iu],nex)-eval(lower[il],nex);
		auto avg_val = [](T a, T b) -> T {
			if (a > b) swap(a,b);
			if (b <= 0) return 0;
			if (a >= 0) return (a+b)/2;
			return b/(b-a)*b/2;
		};
		ans += (nex-lst)*avg_val(lst_dif,nex_dif);
		assert(x.x <= nex && nex <= x.y);
		lst = nex, lst_dif = nex_dif;
		iu += lst == nex_upper;
		il += lst == nex_lower;
	}
	return ans;
}

Half plane_right(pt a, pt b) { // half-plane to right of a -> b
	return {b.y-a.y,a.x-b.x,(b.y-a.y)*a.x+(a.x-b.x)*a.y}; 
}
Half plane_through(pt p, pt dir) { // half-plane through p in direction dir
	return {dir.x,dir.y,dot(p,dir)}; 
}
