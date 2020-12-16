const int mod = 998244353;
inline int add(int a, int b) { return ((a+b < mod) ? (a+b) : (a+b-mod)); }
inline int sub(int a, int b) { return ((a-b >= 0) ? (a-b) : (a-b+mod)); }
int mult(int a, int b) { return int(ll(a) * b % mod); }
int binpow(int a, int p) {
    int res = 1;
    for (; p; p /= 2) {
        if (p & 1) res = mult(res, a);
        a = mult(a, a);
    }
    return res;
}
int divi(int a, int b) { return mult(a, binpow(b, mod - 2)); }

int fact[maxn];
int invf[maxn];
void init() {
    fact[0] = 1;
    for (int i = 1; i < maxn; ++i) fact[i] = mult(fact[i - 1], i);
    for (int i = 0; i < maxn; ++i) invf[i] = divi(1, fact[i]);
}
int C(int n, int k) {
    int res = fact[n];
    res = mult(res, invf[k]);
    res = mult(res, invf[n - k]);
    return res;
}
int Crep(int n, int k) {
    return C(n + k - 1, n);
}
