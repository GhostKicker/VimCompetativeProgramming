struct stree{
    int n = 1;
    vector<int> t;
    stree(){}
    stree(vector<int>& v){
        while(n < (int)v.size()) n *= 2;
        t.resize(2*n, inf);
        for (int i = 0; i < (int)v.size(); ++i) t[i+n] = v[i];
        for (int i = n-1; i; --i) t[i] = min(t[i+i], t[i+i+1]);
    }
    void set(int i, int x){
        t[i+=n] = x;
        for (i/=2; i; i/=2) t[i] = min(t[i+i], t[i+i+1]);
    }
    int get(int l, int r){
        int res = inf;
        for (l+=n, r+=n; l<=r; l/=2, r/=2){
            if (l % 2 == 1) res = min(res, t[l++]);
            if (r % 2 == 0) res = min(res, t[r--]);
        }
        return res;
    }
};
 
struct HeavyLightDecomposition{
    vector<vector<int>> g;          //your instance of graph
    vector<stree> dec;              //structures: trees or tables or whatever
    vector<int> conn;               //vertex to which structs connect
    vector<pair<int,int>> ind;      //indexes of vertices: number of struct and index inside struct
    vector<int> sz;                 //sizes of subtrees;
    vector<int> dep;                //depth of vertices;
    static const int maxpw = 25;    //maximum depth of graph is 2^maxpw
    vector<array<int, maxpw>> par;  //parents for lca
 
    void dfs(int v, int p, int d){
        //for calculating lca, sz, dep
        par[v][0] = p;
        dep[v] = d;
        for (int i = 1; i < maxpw; ++i)
            par[v][i] = par[par[v][i-1]][i-1]; 
        for (auto& to : g[v]){
            if (to == p) continue;
            dfs(to, v, d+1);
            sz[v] += sz[to];
        }
    }
 
    void dfs_build(int v, int p, vector<int>& tmp, vector<int>& vals){
        //for building decomposition itself
        if ((int)tmp.size() == 0) conn.push_back(p);
        ind[v] = make_pair((int)dec.size(), (int)tmp.size());
        tmp.push_back(vals[v]);
        sort(g[v].begin(), g[v].end(), [&](int a, int b){return sz[a] > sz[b];});
 
        int sons = 0;
        for (auto& to : g[v]){
            if (to == p) continue;
            if (sons != 0) tmp = vector<int>();
            dfs_build(to, v, tmp, vals);
            ++sons;
        }
        if (sons == 0) dec.push_back(stree(tmp));
    }
 
    HeavyLightDecomposition(){}
    HeavyLightDecomposition(vector<vector<int>>& gg, vector<int> vals){
        //takes graph and values in vertices
        g = gg;
        int n = (int)g.size();
        sz.assign(n, 1);
        dep.resize(n);
        ind.resize(n);
        par.resize(n);
        dfs(0, 0, 0);
        //for (auto& it : sz) cout << it << " ";
        //cout << endl;
        vector<int> tmp;
        dfs_build(0, 0, tmp, vals);
    }
    int getpar(int v, int up){
        //this is for lca
        for (int curpw = maxpw - 1; curpw >= 0; --curpw)
            if ((up >> curpw) & 1) v = par[v][curpw];
        return v;
    }
    int LCA(int a, int b){
        if (dep[a] < dep[b]) swap(a, b);
        a = getpar(a, dep[a] - dep[b]);
        if (a == b) return a;
        for (int curpw = maxpw - 1; curpw >= 0; --curpw){
            if (par[a][curpw] == par[b][curpw]) continue;
            a = par[a][curpw];
            b = par[b][curpw];
        }
        return par[a][0];
    }
 
    void set(int v, int x){
        dec[ind[v].first].set(ind[v].second, x);
    }
    int get(int a, int b){
        //be careful with ranges for every .get operation
        int c = LCA(a, b);
        int res = inf;
        while(ind[a].first != ind[c].first){
            res = min(res, dec[ind[a].first].get(0, ind[a].second));
            a = conn[ind[a].first];
        }
        if (a != c) res = min(res, dec[ind[a].first].get(ind[c].second + 1, ind[a].second));
        swap(a, b);
        while(ind[a].first != ind[c].first){
            res = min(res, dec[ind[a].first].get(0, ind[a].second));
            a = conn[ind[a].first];
        }
        if (a != c) res = min(res, dec[ind[a].first].get(ind[c].second + 1, ind[a].second));
 
        //if decompositon is on edges, you dont need next line
        //but you still need to give vertices values
        res = min(res, dec[ind[c].first].get(ind[c].second, ind[c].second));
        return res;
    }
    
};
