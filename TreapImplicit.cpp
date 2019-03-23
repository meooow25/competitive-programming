// Basic implicit treap template
// Refs: https://cp-algorithms.com/data_structures/treap.html
//       https://en.wikipedia.org/wiki/Treap

// TODO: Update this to be similar to Treap.cpp

namespace ImplicitTreap {
    const int POOL_SZ = 5e6;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    struct node {
        int val;
        unsigned prio;
        int lt, rt, sz;
    } P[POOL_SZ];
    int pool_cur = 1;

    inline int newnode(int val) {
        P[pool_cur].val = val;
        P[pool_cur].prio = rng();
        P[pool_cur].sz = 1;
        return pool_cur++;
    }

    inline int getsz(int idx) { return idx == 0 ? 0 : P[idx].sz; }
    inline void update(int idx) { if (idx) P[idx].sz = getsz(P[idx].lt) + 1 + getsz(P[idx].rt); }

    void display(int idx) {
        if (!idx) return;
        display(P[idx].lt);
        cout << P[idx].val << " ";
        display(P[idx].rt);
    }

    void merge(int lt, int rt, int &idx) {
        if (!lt) idx = rt;
        else if (!rt) idx = lt;
        else if (P[lt].prio > P[rt].prio)
            merge(P[lt].rt, rt, P[lt].rt), idx = lt;
        else
            merge(lt, P[rt].lt, P[rt].lt), idx = rt;
        update(idx);
    }

    // Split into [1..pos] and [pos+1..end]
    void split(int idx, int pos, int &lt, int &rt) {
        if (!idx) { lt = rt = 0; return; }
        int curpos = getsz(P[idx].lt) + 1;
        if (pos < curpos)
            split(P[idx].lt, pos, lt, P[idx].lt), rt = idx;
        else
            split(P[idx].rt, pos - curpos, P[idx].rt, rt), lt = idx;
        update(idx);
    }

    void insert(int &idx, int pos, int val) {
        int rt;
        split(idx, pos - 1, idx, rt);
        merge(idx, newnode(val), idx);
        merge(idx, rt, idx);
    }

    void remov(int &idx, int pos) {
        int curpos = getsz(P[idx].lt) + 1;
        if (pos == curpos)
            merge(P[idx].lt, P[idx].rt, idx);
        else if (pos < curpos)
            remov(P[idx].lt, pos);
        else
            remov(P[idx].rt, pos - curpos);
        update(idx);
    }
}


namespace PersistentImplicitTreap {
    const int POOL_SZ = 5e6;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    struct node {
        int val;
        unsigned prio;
        int lt, rt, sz;
    } P[POOL_SZ];
    int pool_cur = 1;

    inline int newnode(int val) {
        P[pool_cur].val = val;
        P[pool_cur].prio = rng();
        P[pool_cur].sz = 1;
        return pool_cur++;
    }

    inline int copynode(int idx) {
        P[pool_cur] = P[idx];
        return pool_cur++;
    }

    inline int getsz(int idx) { return idx == 0 ? 0 : P[idx].sz; }
    inline void update(int idx) { if (idx) P[idx].sz = getsz(P[idx].lt) + 1 + getsz(P[idx].rt); }

    void display(int idx) {
        if (!idx) return;
        display(P[idx].lt);
        cout << P[idx].val << " ";
        display(P[idx].rt);
    }

    void merge(int lt, int rt, int &idx) {
        if (!lt) idx = rt;
        else if (!rt) idx = lt;
        else if (P[lt].prio > P[rt].prio) {
            idx = copynode(lt);
            merge(P[idx].rt, rt, P[idx].rt);
        } else {
            idx = copynode(rt);
            merge(lt, P[idx].lt, P[idx].lt);
        }
        update(idx);
    }

    // Split into [1..pos] and [pos+1..end]
    void split(int idx, int pos, int &lt, int &rt) {
        if (!idx) { lt = rt = 0; return; }
        int curpos = getsz(P[idx].lt) + 1;
        idx = copynode(idx);
        if (pos < curpos)
            split(P[idx].lt, pos, lt, P[idx].lt), rt = idx;
        else
            split(P[idx].rt, pos - curpos, P[idx].rt, rt), lt = idx;
        update(idx);
    }

    int insert(int idx, int pos, int val) {
        int idx2;
        split(idx, pos - 1, idx, idx2);
        merge(idx, newnode(val), idx);
        merge(idx, idx2, idx);
        return idx;
    }

    void _remov(int &idx, int pos) {
        idx = copynode(idx);
        int curpos = getsz(P[idx].lt) + 1;
        if (pos == curpos)
            merge(P[idx].lt, P[idx].rt, idx);
        else if (pos < curpos)
            _remov(P[idx].lt, pos);
        else
            _remov(P[idx].rt, pos - curpos);
        update(idx);
    }

    int remov(int idx, int pos) {
        _remov(idx, pos);
        return idx;
    }
}
