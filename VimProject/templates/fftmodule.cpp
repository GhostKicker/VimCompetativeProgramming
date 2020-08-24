
const int MOD = 998244353;
ll qp(ll a, ll b){
    while (b<0) b += MOD - 1;
    ll x = 1; a %= MOD;
    while (b){
        if (b & 1) x = x*a%MOD;
        a = a*a%MOD; b >>= 1;
    }
    return x;
}
int *w0[2333], *w1[2333];
int getK(int n)
{
    int s = 1; while (s<n) s <<= 1; return s;
}
void prep(int K)
{
    static int pool[1048576 * 4 + 3], *p = pool, i = 1, j = 1;
    for (; j <= K; ++i, j <<= 1){
        w0[i] = p; w1[i] = (p += j); p += j;
        ll g = qp(3, (MOD - 1) >> i), ig = qp(g, MOD - 2);
        w0[i][0] = w1[i][0] = 1;
        for (int k = 1; k<j; ++k)
            w0[i][k] = w0[i][k - 1] * g%MOD,
            w1[i][k] = w1[i][k - 1] * ig%MOD;
    }
}
void fft(int* x, int K, int v)
{
    prep(K);
    for (int i = 0, j = 0; i<K; i++){
        if (i>j) swap(x[i], x[j]);
        for (int l = K >> 1; (j ^= l)<l; l >>= 1);
    }
    for (int i = 0; i<K; i++) x[i] = (x[i] % MOD + MOD) % MOD;
    for (int i = 2, c = 1; i <= K; i <<= 1, ++c)
        for (int *w = v ? w1[c] : w0[c], j = 0; j<K; j += i)
            for (int h = i >> 1, a, b, l = 0; l<h; ++l){
                a = x[j + l]; if (a >= MOD) a -= MOD;
                b = (ll)x[j + h + l] * w[l] % MOD,
                    x[j + h + l] = a - b + MOD, x[j + l] = a + b;
            }
    for (int i = 0; i<K; i++) x[i] = (x[i] % MOD + MOD) % MOD;
    if (!v) return;
    ll rv = qp(K, MOD - 2);
    for (int i = 0; i<K; i++) x[i] = x[i] * rv%MOD;
}
vector<int> operator * (const vector<int>& a, const vector<int>& b)
{
    static int p[4*1048576], q[4*1048576];
    int w = a.size() + b.size() - 1;
    vector<int> c; c.resize(w);
    if (b.size()<13){
        for (int i = 0; i<(int)a.size(); ++i)
            for (int j = 0; j<(int)b.size(); ++j)
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
        return c;
    }
    int K = getK(w);
    for (int i = 0; i<K; ++i) p[i] = q[i] = 0;
    for (int i = 0; i<(int)a.size(); ++i) p[i] = a[i];
    for (int i = 0; i<(int)b.size(); ++i) q[i] = b[i];
    fft(p, K, 0); fft(q, K, 0);
    for (int i = 0; i<K; ++i)
        p[i] = p[i] * (ll)q[i] % MOD;
    fft(p, K, 1);
    for (int i = 0; i<w; ++i) c[i] = p[i];
    return c;
}