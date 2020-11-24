#include <bits/stdc++.h>
using namespace std;

namespace Generator {
    const int maxn = (1 << 17);
    int used[maxn]; //idea similar to segment tree
    int usedused[maxn];

    mt19937_64 rng(time(0));
    //mt19937_64 rng(1);
    int getnext() {
        int res = -1;
        while (res == -1 || res < 2) {
            res = rng() % maxn;
        }
        return res;
    }

    string getbinary(int a) {
        string res = "";
        while (a > 1) {
            char next = ('0' + (a & 1));
            res.push_back(next);
            a /= 2;
        }
        reverse(begin(res), end(res));
        return res;
    }


    void update_used_down(int a) {
        if (a >= maxn) return;
        if (used[a] == 1) return;
        used[a] = 1;
        update_used_down(a + a);
        update_used_down(a + a + 1);
    }
    void update_used_up(int a) {
        while (a > 1) {
            used[a] = 1;
            a /= 2;
        }
    }
    void update_used(int a) {
        update_used_down(a);
        update_used_up(a);
    }

    vector<string> solve(int n, int pref) {

        vector<int> output;
        fill(used, used + maxn, 0);
        fill(usedused, usedused + maxn, 0);

        n -= pref;

        //generate with unique prefixes
        for (int i = 0; i < n; ++i) {
            int cur = -1;
            while (cur == -1 || used[cur] == 1) {
                cur = getnext();
            }
            output.push_back(cur);
            update_used(cur);
            usedused[cur] = 1;
        }

        vector<int> used_idx;
        for (int i = 0; i < maxn; ++i)
            if (used[i]) used_idx.push_back(i);

        //generate prefixes
        for (int i = 0; i < pref; ++i) {
            int cur = -1;
            while (cur == -1 || usedused[cur] == 1) {
                int idx = int(rng() % used_idx.size());
                cur = used_idx[idx];
            }
            output.push_back(cur);
            usedused[cur] = 1;
        }

        //shuffle result
        shuffle(begin(output), end(output), rng);

        vector<string> resres;
        for (auto& it : output) {
            resres.push_back(getbinary(it));
            //cout << getbinary(it) << endl;
        }
        return resres;
    }
}


int checker(vector<string>& vs) {
    int res = 0;
    set<string> s;
    for (auto& it : s) {
        s.insert(it);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed << setprecision(10);
    cin.tie(nullptr);
#ifdef _MY
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n = 1000;
    int cnt = 0;
    for (int i = 0; i < 10; ++i){
        string test = "test";
        test = test + char(i / 10 + '0') + char(i % 10 + '0') + ".in";
        ofstream out(test.c_str());

        int pref = 0;
        //while (pref == -1 || pref > 900) pref = Generator::rng() % 1000;
        auto input = Generator::solve(n, pref);
        cout << checker(input) << endl;
        out << input.size() << endl;
        for (auto& it : input) out << it << endl;
    }


}
