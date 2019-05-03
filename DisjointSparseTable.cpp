// Disjoint sparse table
// For range queries without updates
// O(n log n) to build, O(1) per query

// Refs:
// https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404

// Problems:
// https://codeforces.com/contest/1107/problem/G
// https://codeforces.com/contest/875/problem/D

template <typename T, typename F>
struct DisjointSparseTable {
    vector<vector<T>> t;
    F f;

    template <typename It>
    DisjointSparseTable(int n, It a, F _f): f(_f) {
        // a[i] should be accessible upto the nearest power of 2
        int lgn = max(1, __lg(n) + ((n & (n - 1)) > 0));
        n = 1 << lgn;
        t.assign(lgn, vector<T>(n));
        for (int h = 0, d = 1; d < n; h++, d *= 2) {
            for (int i = d; i <= n; i += 2 * d) {
                t[h][i - 1] = a[i - 1];
                for (int j = i - 2; j >= i - d; j--)
                    t[h][j] = f(a[j], t[h][j + 1]);
                t[h][i] = a[i];
                for (int j = i + 1; j < i + d; j++)
                    t[h][j] = f(t[h][j - 1], a[j]);
            }
        }
    }

    T query(int l, int r) {
        if (l == r) return t[0][l];
        int h = __lg(l ^ r);
        return f(t[h][l], t[h][r]);
    }
};
