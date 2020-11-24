ll binpow(ll a, ll p)
{
    ll res = 1;
    for (; p; p >>= 1)
    {
        if (p & 1) res *= a;
        a *= a;
    }
    return res;
}