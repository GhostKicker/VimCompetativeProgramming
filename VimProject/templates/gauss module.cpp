namespace Gauss {
    typedef vector<int> vi;
    const int inf = int(1e9 + 7);
    int binpow(int a, int p) {
        int res = 1;
        for (; p; p >>= 1) {
            if (p & 1)res = res * a % inf;
            a = a * a % inf;
        }
        return res;
    }

    int sub(int a, int b) {
        int res = a - b;
        res %= inf;
        res += inf;
        res %= inf;
        return res;
    }

    vi gauss(vector<vi> a, vi b) {
        int n = a.size();
        for (int row = 0; row < n; ++row) {
            bool good = false;
            for (int col = row; col < n; ++col) {
                if (a[row][col] == 0) continue;
                good = true;
                swap(a[row], a[col]);
                swap(b[row], b[col]);
                break;
            }
            if (!good) continue;

            int div = binpow(a[row][row], inf - 2);
            for (int col = 0; col < n; ++col) a[row][col] = a[row][col] * div % inf;
            b[row] = b[row] * div % inf;

            for (int currow = row + 1; currow < n; ++currow) {
                if (a[currow][row] == 0) continue;
                int mult = a[currow][row];
                for (int col = 0; col < n; ++col) a[currow][col] = sub(a[currow][col], a[row][col] * mult);
                b[currow] = sub(b[currow], b[row] * mult);
            }
        }

        for (int row = n - 1; row >= 0; --row) {
            int div = binpow(a[row][row], inf - 2);
            for (int col = 0; col < n; ++col) a[row][col] = a[row][col] * div % inf;
            b[row] = b[row] * div % inf;

            for (int currow = 0; currow < row; ++currow) {
                int mult = a[currow][row];
                for (int col = 0; col < n; ++col) a[currow][col] = sub(a[currow][col], a[row][col] * mult);
                b[currow] = sub(b[currow], b[row] * mult);
            }
        }

        for (int i = 0; i < n; ++i) {
            b[i] *= binpow(a[i][i], inf - 2);
            b[i] %= inf;
            a[i][i] = 1;
        }
        return b;
    }
}
using namespace Gauss;
