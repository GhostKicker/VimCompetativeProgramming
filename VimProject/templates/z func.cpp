template<class t>
vector<int> z_func(t s) {
    vector<int> z(s.size(), 0);
    int l = 0;
    int r = 0;
    for (int i = 1; i < s.size(); i++) {
        int count = 0;
        if (i <= r)  count = min(z[i - l], r - i + 1);
        for (int j = count; i + j < s.size() && s[j] == s[i + j]; j++)
            count++;
        z[i] = count;
        if (i + count >= r){
            l = i;
            r = i + count - 1;
        }
    }
    return z;
}