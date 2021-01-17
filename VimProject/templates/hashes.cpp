const long long maxn = 1000004;
const pair<long long, long long> p = make_pair(263, 263);
pair<long long, long long> invp; //k^{-1} % mod == k^{mod - 2} % mod
const pair<long long, long long> mod = make_pair(1000000007, 1000000009);
long long binpow(long long a, long long p, long long m){
    long long res = 1;
    for (; p>0; p/=2){
        if (p % 2 == 1) res = res * a % m;
        a = a * a % m;
    }
    return res;
}
pair<long long, long long> pw[maxn]; //p^{0}, p^{1}, p^{2}, ....
pair<long long, long long> invpw[maxn];//p^{0}, p^{-1}, p^{-2}, ...
int initialized = 0;
void init_hashes(){
    if (initialized == 1) return;
    initialized = 1;
    invp.first = binpow(p.first, mod.first - 2, mod.first);
    invp.second = binpow(p.second, mod.second - 2, mod.second);
    pw[0] = make_pair(1ll, 1ll);
    invpw[0] = make_pair(1ll, 1ll);
    for (int i = 1; i < maxn; ++i){
        pw[i].first = pw[i-1].first * p.first % mod.first;
        pw[i].second = pw[i-1].second * p.second % mod.second;
        invpw[i].first = invpw[i-1].first * invp.first % mod.first;
        invpw[i].second = invpw[i-1].second * invp.second % mod.second;
    }
}

struct myhash{
    vector<pair<long long, long long>> h;
    myhash(){init_hashes();}
    myhash(string s){
        init_hashes();
        for (int i = 0; i < (int)s.size(); ++i){
            h.push_back(pair<long long, long long>());
            h.back().first = s[i] * pw[i].first % mod.first;
            h.back().second = s[i] * pw[i].second % mod.second;
            if (i != 0) {
                h[i].first = (h[i].first + h[i-1].first) % mod.first;
                h[i].second = (h[i].second + h[i-1].second) % mod.second;
            }
        }
    }
    //including borders
    pair<long long, long long> get_hash(int l, int r){
        pair<long long, long long> res = h[r];
        if (l != 0) res.first += mod.first - h[l-1].first;
        if (l != 0) res.second += mod.second - h[l-1].second;
        res.first = res.first * invpw[l].first % mod.first;
        res.second = res.second * invpw[l].second % mod.second;
        return res;
    }
    size_t size(){ return h.size(); }
};
