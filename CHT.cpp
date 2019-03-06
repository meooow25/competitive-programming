
// Maintains max convex hull of lines
// insertRight: insert line with max slope
// insertLeft: insert line with min slope
// queryRight: get max while popping from right
// queryLeft: get max while popping from left
// query: get max by binary search

struct ConvexHull {
    struct line {
        long long m, c;
        long long eval(long long x) { return m * x + c; }
        long double isectX(line l) { return (long double) (c - l.c) / (l.m - m); }
    };

    const int MAX_SIZE = 1e6;

    deque<line> dq;
    vector<int> ints;

    ConvexHull(): ints(MAX_SIZE) {
        iota(ints.begin(), ints.end(), 0);
    }

    void insertRight(line l) {
        if (!dq.empty() && dq.back().m == l.m) {
            if (dq.back().c >= l.c) return;
            dq.pop_back();
        }
        while (dq.size() >= 2 && l.isectX(dq.back()) <= dq.back().isectX(dq[dq.size() - 2]))
            dq.pop_back();
        dq.push_back(l);
    }

    void insertLeft(line l) {
        if (!dq.empty() && dq[0].m == l.m) {
            if (dq[0].c >= l.c) return;
            dq.pop_front();
        }
        while (dq.size() >= 2 && l.isectX(dq[0]) >= dq[0].isectX(dq[1]))
            dq.pop_front();
        dq.push_front(l);
    }

    long long queryRight(long long x) {
        while (dq.size() >= 2 && dq.back().eval(x) <= dq[dq.size() - 2].eval(x))
            dq.pop_back();
        return dq.back().eval(x);
    }

    long long queryLeft(long long x) {
        while (dq.size() >= 2 && dq[0].eval(x) <= dq[1].eval(x))
            dq.pop_front();
        return dq[0].eval(x);
    }

    long long query(long long x) {
        // Find a better way than making the same lambda for every search.
        // std::function is too slow.
        auto cmp = [this](int idx, long long x) { return dq[idx].isectX(dq[idx + 1]) < x; };
        int idx = *lower_bound(ints.begin(), ints.begin() + dq.size() - 1, x, cmp);
        return dq[idx].eval(x);
    }
}