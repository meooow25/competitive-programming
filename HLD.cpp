// Heavy-light decomposition
// Decompose a tree such that a path from root to any node
// is split into at most lg n pieces.

namespace HLD {

    vector<int> par, dep, heavy, head, pos;
    int cur_pos;

    int dfs(int u, vector<int> g[]) {
        int sz = 1, mx_sz = 0;
        for (int v : g[u]) if (v != par[u]) {
            par[v] = u, dep[v] = dep[u] + 1;
            int v_sz = dfs(v, g);
            sz += v_sz;
            if (v_sz > mx_sz)
                mx_sz = v_sz, heavy[u] = v;
        }
        return sz;
    }

    void decompose(int u, int h, vector<int> g[]) {
        head[u] = h, pos[u] = ++cur_pos;
        if (heavy[u] != -1)
            decompose(heavy[u], h, g);
        for (int v : g[u]) if (v != par[u] && v != heavy[u])
            decompose(v, v, g);
    }

    void init(vector<int> g[], int n) {
        par = vector<int>(n + 1);
        dep = vector<int>(n + 1);
        heavy = vector<int>(n + 1, -1);
        head = vector<int>(n + 1);
        pos = vector<int>(n + 1);
        cur_pos = 0;

        dfs(1, g);
        decompose(1, 1, g);
    }

    inline void pathstuff(int u, int v) {
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            // Do stuff on [pos[head[v]]..pos[v]]
        }
        if (dep[u] > dep[v]) swap(u, v);
        // Do stuff on [pos[u]..pos[v]]
    }

    inline void vertexstuff(int u) {
        // Do stuff on pos[u]
    }
}

// Problems
// https://www.spoj.com/problems/QTREE/
// https://www.codechef.com/SNCKEL19/problems/ADITREE
