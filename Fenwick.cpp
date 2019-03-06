struct Fenwick {
    int n;
    vector<int> t;

    Fenwick(int n_): n(n_), t(n_ + 1) {}

    int query(int i) {
        int v = 0;
        for (; i > 0; i -= (i & -i)) v += t[i];
        return v;
    }

    int query(int i, int j) {
        return query(j) - query(i - 1);
    }

    void update(int i, int v) {
        for (; i <= n; i += (i & -i)) t[i] += v;
    }
};

// Compact
struct Fenwick {
    int n; vector<int> t;
    Fenwick(int n_): n(n_), t(n_ + 1) {}
    int query(int i) { int v = 0; for (; i > 0; i -= (i & -i)) v += t[i]; return v; }
    int query(int i, int j) { return query(j) - query(i - 1); }
    void update(int i, int v) { for (; i <= n; i += (i & -i)) t[i] += v; }
};