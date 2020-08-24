vi sufarray(string s)
{
    vi p;
    vi c;

    s += char(int(31));
    int n = s.size();

    p.resize(n);
    c.resize(n);

    c[0] = 0;
    for (int i = 0; i < n; i++)
    {
        p[i] = i;
    }

    sort(all(p), [&s](int a, int b) { return s[a] < s[b]; });

    int curclass = 0;
    c[p[0]] = 0;
    for (int i = 1; i < n; i++)
    {
        if (s[p[i]] != s[p[i - 1]]) ++curclass;
        c[p[i]] = curclass;
    }


    for (int i = 2; i < n; i <<= 1)
    {
        vi cswap(n, inf);
        vector<pii> next;
        for (int j = 0; j < n; j++)
            next.pb({ p[j], (p[j] + (i >> 1)) % n });

        sort(all(next),
            [&c](pii a, pii b)
            {
                if (c[a.first] != c[b.first]) return c[a.first] < c[b.first];
                return c[a.second] < c[b.second];
            });

        for (int j = 0; j < next.size(); j++)
        {
            p[j] = next[j].first;
        }

        int curclass = 0;
        cswap[p[0]] = 0;
        for (int j = 1; j < n; ++j)
        {
            pii& a = next[j];
            pii& b = next[j - 1];
            if (c[a.first] != c[b.first] || c[a.second] != c[b.second]) ++curclass;
            cswap[p[j]] = curclass;
        }

        swap(c, cswap);

    }

    vi res(p.begin() + 1, p.end());
    return res;

}
