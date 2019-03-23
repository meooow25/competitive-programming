// Treap

// Simple join-based treap implementation
// Allows multiple nodes with same key
// O(log n) per operation

// Refs: https://cp-algorithms.com/data_structures/treap.html
//       https://en.wikipedia.org/wiki/Treap
//       https://en.wikipedia.org/wiki/Join-based_tree_algorithms

// Problems: https://cses.fi/problemset/task/1144/

// TODO: Add persistent version

namespace Treap {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    struct node {
        int key;
        unsigned prio;
        int lt, rt, sz;
    };
    vector<node> P(1);

    inline int newnode(int key) {
        P.push_back({key, rng(), 0, 0, 1});
        return P.size() - 1;
    }

    inline int getsz(int idx) { return idx == 0 ? 0 : P[idx].sz; }
    inline void update(int idx) { if (idx) P[idx].sz = getsz(P[idx].lt) + 1 + getsz(P[idx].rt); }

    void merge(int lt, int rt, int &idx) {
        if (!lt) idx = rt;
        else if (!rt) idx = lt;
        else if (P[lt].prio > P[rt].prio)
            merge(P[lt].rt, rt, P[lt].rt), idx = lt;
        else
            merge(lt, P[rt].lt, P[rt].lt), idx = rt;
        update(idx);
    }

    // Split into <= key and > key
    void split(int idx, int key, int &lt, int &rt) {
        if (!idx) { lt = rt = 0; return; }
        if (key < P[idx].key)
            split(P[idx].lt, key, lt, P[idx].lt), rt = idx;
        else
            split(P[idx].rt, key, P[idx].rt, rt), lt = idx;
        update(idx);
    }

    void insert(int &idx, int key) {
        int rt;
        split(idx, key - 1, idx, rt);
        merge(idx, newnode(key), idx);
        merge(idx, rt, idx);
    }

    void remov(int &idx, int key) {
        if (!idx) return;
        if (key == P[idx].key)
            merge(P[idx].lt, P[idx].rt, idx);
        else if (key < P[idx].key)
            remov(P[idx].lt, key);
        else
            remov(P[idx].rt, key);
        update(idx);
    }
}
