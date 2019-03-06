template <typename T>
struct SegTree {
    struct node {
        int s, e;
        T v;
    };
    vector<node> t;

    SegTree(int n): t(n << 2) {
        build(1, 0, n);
    }

    void build(int i, int s, int e) {
        t[i].s = s, t[i].e = e;
        if (s == e) { t[i].v = T::at(s); return; }
        int m = (s + e) >> 1;
        build(i << 1, s, m); build(i << 1 | 1, m + 1, e);
        t[i].v = T(t[i << 1].v, t[i << 1 | 1].v);
    }

    void push(int i) {
        if (t[i].s < t[i].e) t[i].v.push(t[i << 1].v, t[i << 1 | 1].v);
        t[i].v.apply();
    }

    void update(int i, int us, int ue, auto v) {
        push(i);
        if (ue < t[i].s || t[i].e < us) return;
        if (us <= t[i].s && t[i].e <= ue) { t[i].v.store(v); push(i); return; }
        update(i << 1, us, ue, v); update(i << 1 | 1, us, ue, v);
        t[i].v = T(t[i << 1].v, t[i << 1 | 1].v);
    }

    T query(int i, int qs, int qe) {
        if (qe < t[i].s || t[i].e < qs) return T();
        push(i);
        if (qs <= t[i].s && t[i].e <= qe) return t[i].v;
        return T(query(i << 1, qs, qe), query(i << 1 | 1, qs, qe));
    }
};

struct data {
    int len; long long sum, lazy;
    data(): len(0), sum(0), lazy(0) {}
    data(int x): len(1), sum(x), lazy(0) {}
    static data at(int i) {
        return data(0);
    }
    data(data l, data r) {
        len = l.len + r.len;
        sum = l.sum + r.sum;
        lazy = 0;
    }
    void store(long long delta) { lazy += delta; }
    void push(data &l, data &r) { l.store(lazy), r.store(lazy); }
    void apply() { sum += len * lazy; lazy = 0; }
};