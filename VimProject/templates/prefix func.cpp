template<class t>
vector<int> p_func(t s) {
    int n = s.size();
    vector<int> p(n, 0);
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1];
        while (p[i] > 0 && s[i] != s[p[i]])
            p[i] = p[p[i] - 1];
        if (s[i] == s[p[i]]) p[i]++;
    }
    return p;
}