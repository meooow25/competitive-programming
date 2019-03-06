
// LiChao Segment Tree
// Supports insertion of lines and min queries

// https://e-maxx-eng.appspot.com/geometry/convex_hull_trick.html

namespace LiChao {
    const long long INF = 1e18;
    const int MAX_NODES = 1e6;
    struct line {
        long long m, c;
        inline long long eval(long long x) { return m * x + c; }
    };
    struct node {
        int s, e, m;
        line cur{0, INF};
        int lt = 0, rt = 0;
        node() {}
        node(int ss, int ee): s(ss), e(ee), m((ss + ee) >> 1) {}
    } T[MAX_NODES];
    int p = 1;

    int newnode(int ss, int ee) {
        T[p] = node(ss, ee);
        return p++;
    }

    long long query(int i, int x) {
        node &n = T[i];
        long long y = n.cur.eval(x);
        if (n.s == n.e) return y;
        if (x < n.m && n.lt) y = min(y, query(n.lt, x));
        if (x > n.m && n.rt) y = min(y, query(n.rt, x));
        return y;
    }

    void insert(int i, line l) {
        node &n = T[i];
        if (n.cur.c == INF) { n.cur = l; return; }
        bool b1 = l.eval(n.s) < n.cur.eval(n.s);
        bool b2 = l.eval(n.m) < n.cur.eval(n.m);
        bool b3 = l.eval(n.e) < n.cur.eval(n.e);
        if (b2) swap(n.cur, l);
        if (b1 == b2 && b2 == b3) return;
        if (n.s == n.e) return;
        if (b1 != b2) { if (!n.lt) n.lt = newnode(n.s, n.m); insert(n.lt, l); }
        else { if (!n.rt) n.rt = newnode(n.m + 1, n.e); insert(n.rt, l); }
    }
};

// Also keep the lines
namespace LiChao {
    const long long INF = 1e18;
    const int MAX_NODES = 1e6;
    struct line {
        long long m, c;
        inline long long eval(long long x) { return m * x + c; }
    };
    struct node {
        int s, e, m;
        line cur{0, INF};
        int lt = 0, rt = 0;
        vector<line> lines;
        node() {}
        node(int ss, int ee): s(ss), e(ee), m((ss + ee) >> 1) {}
    } T[MAX_NODES];
    int p = 1;

    int newnode(int ss, int ee) {
        T[p] = node(ss, ee);
        return p++;
    }

    long long query(int i, int x) {
        node &n = T[i];
        long long y = n.cur.eval(x);
        if (n.s == n.e) return y;
        if (x < n.m && n.lt) y = min(y, query(n.lt, x));
        if (x > n.m && n.rt) y = min(y, query(n.rt, x));
        return y;
    }

    void insert(int i, line l) {
        T[i].push_back(l);
        insert_(i, l);
    }

    void insert_(int i, line l) {
        node &n = T[i];
        if (n.cur.c == INF) { n.cur = l; return; }
        bool b1 = l.eval(n.s) < n.cur.eval(n.s);
        bool b2 = l.eval(n.m) < n.cur.eval(n.m);
        bool b3 = l.eval(n.e) < n.cur.eval(n.e);
        if (b2) swap(n.cur, l);
        if (b1 == b2 && b2 == b3) return;
        if (n.s == n.e) return;
        if (b1 != b2) { if (!n.lt) n.lt = newnode(n.s, n.m); insert_(n.lt, l); }
        else { if (!n.rt) n.rt = newnode(n.m + 1, n.e); insert_(n.rt, l); }
    }
};
