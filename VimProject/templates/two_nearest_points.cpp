double mindist(vector<pair<int,int>> pts){
    mt19937 rng(time(0));
    shuffle(all(pts), rng);
 
    cc_hash_table<long long, vector<int>> table;
    auto coor = [&](pair<int,int> p, double d){
        return pair<int,int>(p.first/d, p.second/d);
    };
    auto gethash = [&](pair<int,int> p){
        return (1ll * p.first * inf + p.second);
    };
    auto rebuild = [&](double d, int p){
        table = cc_hash_table<long long, vector<int>>();
        for (int i = 0; i <= p; ++i){
            table[gethash(coor(pts[i], d))].push_back(i);
        }
    };
    auto dist = [&](pair<int,int>& a, pair<int,int>& b){
        long long dx = a.first - b.first;
        long long dy = a.second - b.second;
        dx *= dx; dy *= dy;
        return dx+dy;
    };
 
    long long res = INF;
 
    for (int i = 0; i < pts.size(); ++i){
        auto c = coor(pts[i], sqrt(res));
        long long curdist = res;
        for (int dx = -1; dx <= 1; ++dx){
            for (int dy = -1; dy <= 1; ++dy){
                pair<int,int> nc(c.first+dx, c.second+dy);
                for (auto& it : table[gethash(nc)]){
                    curdist = min(curdist, dist(pts[i], pts[it]));
                }
            }
        }
 
        table[gethash(coor(pts[i], sqrt(res)))].push_back(i);
        if (curdist != res){
            res = curdist;
            rebuild(sqrt(res), i);
        }
    }
    return sqrt(res);
}
