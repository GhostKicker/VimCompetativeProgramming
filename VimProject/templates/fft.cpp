#include <bits/stdc++.h>
using namespace std;
#define pb  push_back
#define mp  make_pair
#define fs  first
#define sc  second
#define ll  long long
#define vi  vector<int>
#define vvi vector<vi >
#define all(x) x.begin(), x.end()
#define PI  acos(-1.0)

struct base {
    double x, y;
    base (double a = 0, double b = 0) { x = a; y = b; }
};
base operator+(base& a, base& b) { return base(a.x + b.x, a.y + b.y); }
base operator-(base& a, base& b) { return base(a.x - b.x, a.y - b.y); }
base operator*(base& a, base& b) { return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
void operator*=(base& a, base& b) { a = a * b; }
void operator/=(base& a, double n) { a.x /= n; a.y /= n; }

int rev(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; ++i)
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    return res;
}

void fft(vector<base>& a, bool invert) {
    int n = (int)a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)
        ++lg_n;

    for (int i = 0; i < n; ++i)
        if (i < rev(i, lg_n))
            swap(a[i], a[rev(i, lg_n)]);

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            base w(1);
            for (int j = 0; j < len / 2; ++j) {
                base u = a[i + j];
                base v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

int m, n;
vector<base> a, b, c;

void read(vector<base>& v) {
    int k; cin >> k;
    v.resize(k);
    for (int i = 0; i < k; ++i)
        cin >> v[i].x;
}

int main() {
    ios_base::sync_with_stdio(false);
    read(a);
    read(b);
    m = max((int)a.size(), (int)b.size());
    n = 1;
    while (n < m + m)
        n = n + n;
    while (a.size() < n) a.pb(base());
    while (b.size() < n) b.pb(base());
    c.resize(n);

    fft(a, false);
    fft(b, false);
    for (int i = 0; i < n; ++i)
        c[i] = a[i] * b[i];
    fft(c, true);

    return 0;
}