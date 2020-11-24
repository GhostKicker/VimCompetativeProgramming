const long long maxn = 1000004;
const pair<long long, long long> p = make_pair(263, 263);
pair<long long, long long> invp; //k^-1 % mod == k^(mod - 2) % mod
const pair<long long, long long> mod = make_pair(1000000007, 1000000009);
long long binpow(long long a, long long p, long long m){
    long long res = 1;
    for (; p>0; p/=2){
        if (p % 2 == 1) res = res * a % m;
        a = a * a % m;
    }
    return res;
}
pair<long long, long long> pw[maxn]; //p^0, p^1, p^2, ....
pair<long long, long long> invpw[maxn];//p^0, p^-1, p^-2 ...

struct myhash{
    vector<pair<long long, long long>> h;
    myhash(){}
    myhash(string s){
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
};
