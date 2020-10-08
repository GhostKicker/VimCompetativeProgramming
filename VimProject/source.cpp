#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,mmx")
#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <chrono>
//#define int ll
#define F first
#define S second
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define out(x) return void(cout << (x) << endl)
#define OUT(x) ((cout << (x)), exit(0))
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double ld;
const int64_t INF = (int64_t)(2e18);
const int inf = (int)(998244353);
const int maxn = 500 * 1000 + 100;
chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (chrono::steady_clock::now() - cl).count() / 1e9; }
//------------------------------------------//
template<typename T> inline T getint() {
    T val = 0;
    char c;
    bool neg = false;
    while ((c = getchar()) && !(c >= '0' && c <= '9')) {
        neg |= c == '-';
    }
    do {
        val = (val * 10) + c - '0';
    } while ((c = getchar()) && (c >= '0' && c <= '9'));
    return val * (neg ? -1 : 1);
}
//------------------------------------------//

mt19937 rng(time(0));
const int n = 240;
int nums[n];

const int nleft = 15;
const int nmid = 4;
const int nright = 19;

uint32_t mem[(1 << 30) / 4];
inline void mem_set(int i){
    mem[i >> 5] |= (1 << (i & 31));
}
inline int mem_get(int i){
    return (mem[i >> 5] >> (i & 31)) & 1;
}

int left[1 << nleft];
int mid[1 << nmid];
int right[1 << nright];

pair<int,int> dpleft[1 << nleft];
pair<int,int> dpmid[1 << nmid];
int dpright[1 << nright];

int modleft[1 << nleft];
int modmid[1 << nmid];

int leftnum[nleft];
int midnum[nmid];
int rightnum[nright];

unordered_map<int,int> um;
gp_hash_table<int, int> ht;

int inds[300100];
int tofinds[300100];
ll ress[300100];

int32_t main(){
    cl = chrono::steady_clock::now();
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("VimProject/input.txt", "r", stdin);
    freopen("VimProject/output.txt", "w", stdout);
#endif

    //cout << n << endl;
    //for (int i =0 ; i < n; ++i) cout << rng() % inf << endl;
    //cout << 300000 << endl;
    //for (int i = 0; i < 300000; ++i){
    //    cout << rng() % inf << endl;
    //}
    //return 0;

    int _ = getint<int>();
    for (auto& it : nums) it = getint<int>();

    for (int i = 0; i < nleft; ++i) leftnum[i] = nums[i];
    for (int i = 0; i < nmid; ++i) midnum[i] = nums[i + nleft];
    for (int i = 0; i < nright; ++i) rightnum[i] = nums[i + nleft + nmid];

    for (int i = 0; i < (1 << nleft); ++i) dpleft[i].second = i;
    for (int i = 0; i < (1 << nmid); ++i) dpmid[i].second = i;

    for (int cur = 0; cur < nleft; ++cur){
        for (int i = 0; i < (1 << cur); ++i)
            dpleft[i + (1 << cur)].F = (dpleft[i].F + leftnum[cur]) % inf;
    }
    for (int cur = 0; cur < nmid; ++cur){
        for (int i = 0; i < (1 << cur); ++i)
            dpmid[i + (1 << cur)].F = (dpmid[i].F + midnum[cur]) % inf;
    }
    for (int cur = 0; cur < nright; ++cur){
        for (int i = 0; i < (1 << cur); ++i)
            dpright[i + (1 << cur)] = (dpright[i] + rightnum[cur]) % inf;
    }

    for (int i = 0; i < (1 << nright); ++i) 
        ht[dpright[i]] = i;

    int Q = getint<int>();
    vector<int> queries(Q);
    for (auto& it : queries) it = getint<int>();


#ifdef _MY
    cerr << current_time() << endl;
#endif


    shuffle(dpleft, dpleft+(1 << nleft), rng);
    shuffle(dpmid , dpmid +(1 << nmid) , rng);

    int cntbad = 0;
    int num = 0;
    for (int i = 0; i < (1 << nleft); ++i)
        modleft[i] = inf - dpleft[i].F;
    for (int i = 0; i < (1 << nmid); ++i)
        modmid[i] = inf - dpmid[i].F;


    for (int z = 0; z < Q; ++z){
        int x = queries[z];
        for (int i = 0; i < (1 << nleft); ++i){
            int tof = (x + modleft[i]);// % inf;
            if (tof >= inf) tof -= inf;
            if (mem_get(tof) == 0) continue;
            inds[z] = dpleft[i].S;
            tofinds[z] = tof;
            num += i;
            break;
        }
    }

#ifdef _MY
    cerr << current_time() << endl;
#endif

    for (int z = 0; z < Q; ++z){
        um[tofinds[z]] = inds[z];
    }

    for (int mask1 = 0; mask1 < (1 << nmid); ++mask1){
        for (int mask2 = 0; mask2 < (1 << nright); ++mask2){
            int cur = (dpmid[mask1].F + dpright[mask2]);// % inf;
            if (cur >= inf) cur -= inf;
            if (um.count(cur)) um[cur] =  mask1 + (mask2 << nmid);
            //if (ht[cur] != 0) ht[cur] = mask1 + (mask2 << nmid);
            mem_set(cur);
        }
    }




#ifdef _MY
    cerr << current_time() << endl;
#endif

    for (int z = 0; z < Q; ++z){
        ress[z] = ((ll(um[queries[z]]) << nleft) + inds[z]) % inf;
    }

#ifdef _MY
    cerr << current_time() << endl;
#endif

    for (int i = 0; i < Q; ++i){
        cout << ress[i] << " 0 0 0\n";
    }

#ifdef _MY
    cerr << current_time() << endl;
#endif

    return 0;
}
