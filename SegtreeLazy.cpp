template <typename T>
struct SegTree {
    struct node {
        int s, e;
        T v;
    };
    vector<node> t;

    SegTree(int n): t(n * 4) {
        build(1, 1, n);
    }

    void build(int i, int s, int e) {
        t[i].s = s, t[i].e = e;
        if (s == e) { t[i].v = T::at(s); return; }
        int m = (s + e) / 2;
        build(i * 2, s, m); build(i * 2 + 1, m + 1, e);
        t[i].v = T(t[i * 2].v, t[i * 2 + 1].v);
    }

    void push(int i) {
        if (t[i].s < t[i].e) t[i].v.push(t[i * 2].v, t[i * 2 + 1].v);
        t[i].v.apply();
    }

    void update(int i, int us, int ue, const auto& v) {
        push(i);
        if (ue < t[i].s || t[i].e < us) return;
        if (us <= t[i].s && t[i].e <= ue) { t[i].v.store(v); push(i); return; }
        update(i * 2, us, ue, v); update(i * 2 + 1, us, ue, v);
        t[i].v = T(t[i * 2].v, t[i * 2 + 1].v);
    }

    T query(int i, int qs, int qe) {
        if (qe < t[i].s || t[i].e < qs) return T();
        push(i);
        if (qs <= t[i].s && t[i].e <= qe) return t[i].v;
        return T(query(i * 2, qs, qe), query(i * 2 + 1, qs, qe));
    }
};

// Example for +delta on range and sum queries
struct Data {
    int len = 1; long long sum, lazy = 0;
    Data() = default;
    Data(int x): sum(x) {}
    static Data at(int i) {
        return Data(0);
    }
    Data(const Data& l, const Data& r) {
        len = l.len + r.len;
        sum = l.sum + r.sum;
    }
    void store(long long delta) { lazy += delta; }
    void push(Data &l, Data &r) { l.store(lazy), r.store(lazy); }
    void apply() { sum += len * lazy; lazy = 0; }
};
