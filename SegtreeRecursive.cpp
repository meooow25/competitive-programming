struct SegTree {
    struct node {
        int s, e, v;
    };
    vector<node> T;

    SegTree(int n): T(n << 2) {
        build(1, 1, n);
    }

    void build(int i, int s, int e) {
        T[i].s = s, T[i].e = e;
        if (s == e) { T[i].v = 0; return; }
        int m = (s + e) >> 1;
        build(i << 1, s, m); build(i << 1 | 1, m + 1, e);
        T[i].v = max(T[i << 1].v, T[i << 1 | 1].v);
    }

    void update(int i, int j, int v) {
        if (j < T[i].s || T[i].e < j) return;
        if (T[i].s == T[i].e) { T[i].v = v; return; }
        update(i << 1, j, v); update(i << 1 | 1, j, v);
        T[i].v = max(T[i << 1].v, T[i << 1 | 1].v);
    }

    int query(int i, int qs, int qe) {
        if (qe < T[i].s || T[i].e < qs) return 0;
        if (qs <= T[i].s && T[i].e <= qe) return T[i].v;
        return max(query(i << 1, qs, qe), query(i << 1 | 1, qs, qe));
    }
};

template <typename T>
struct SegTree {
    struct node {
        int s, e;
        T v;
    };
    vector<node> t;

    SegTree(int n): t(n << 2) {
        build(1, 1, n);
    }

    void build(int i, int s, int e) {
        t[i].s = s, t[i].e = e;
        if (s == e) { t[i].v = T::at(s); return; }
        int m = (s + e) >> 1;
        build(i << 1, s, m); build(i << 1 | 1, m + 1, e);
        t[i].v = T(t[i << 1].v, t[i << 1 | 1].v);
    }

    void update(int i, int ui, T v) {
        if (ui < t[i].s || t[i].e < ui) return;
        if (t[i].s == t[i].e) { t[i].v = v; return; }
        update(i << 1, ui, v); update(i << 1 | 1, ui, v);
        t[i].v = T(t[i << 1].v, t[i << 1 | 1].v);
    }

    T query(int i, int qs, int qe) {
        if (qe < t[i].s || t[i].e < qs) return T();
        if (qs <= t[i].s && t[i].e <= qe) return t[i].v;
        return T(query(i << 1, qs, qe), query(i << 1 | 1, qs, qe));
    }
};

struct data {
    static const int MIN = -8e8;
    int best, pre, suf, sum;
    data(): best(MIN), pre(MIN), suf(MIN), sum(0) {}
    data(int x): best(x), pre(x), suf(x), sum(x) {}
    static data at(int i) {
        return data(a[i]);
    }
    data(data l, data r) {
        best = max({l.best, r.best, l.suf + r.pre});
        pre = max(l.pre, l.sum + r.pre);
        suf = max(l.suf + r.sum, r.suf);
        sum = l.sum + r.sum;
    }
};