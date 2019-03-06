

struct SegmentTree {
    int N;
    vector<int> tree;

    inline void init(int n) {
        N = 1;
        while(N < n) N <<= 1;
        tree.resize(N << 1);
        fill(tree.begin(), tree.end(), 0);
    }

    inline void update(int i, int j) {
        for (i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if ((i & 1) == 1) tree[i]++;
            if ((j & 1) == 0) tree[j]++;
        }
    }

    inline int query(int i) {
        int v = 0;
        for(i += N; i > 0; i >>= 1)
            v += tree[i];
        return v;
    }
};

struct HeavyLight {
    int N, curpos;
    vector<int> par, dep, heavy, head, pos;
    SegmentTree st;

    void init(vector<int> g[], int n) {
        N = n;
        par.resize(N + 1); dep.resize(N + 1);
        heavy.resize(N + 1); fill(heavy.begin(), heavy.end(), 0);
        head.resize(N + 1); pos.resize(N + 1);
        st.init(N);
        curpos = 0; dep[1] = 0;
        dfs(g, 1);
        decompose(g, 1, 1);
    }

    int dfs(vector<int> g[], int u) {
        int siz = 1, maxsub = 0;
        for (int v : g[u]) if (v != par[u]) {
            par[v] = u;
            dep[v] = dep[u] + 1;
            int sub = dfs(g, v);
            if (sub > maxsub)
                maxsub = sub, heavy[u] = v;
            siz += sub;
        }
        return siz;
    }

    void decompose(vector<int> g[], int u, int h) {
        head[u] = h, pos[u] = curpos++;
        if (heavy[u])
            decompose(g, heavy[u], h);
        for (int v : g[u]) if (v != par[u] && v != heavy[u])
            decompose(g, v, v);
    }

    /** Mode 1 **/
    inline int query(int u) {
        return st.query(pos[u]);
    }

    inline void update(int u, int v, int w) {
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            st.update(pos[head[v]], pos[v], w);
        }
        if (dep[u] > dep[v]) swap(u, v);
        st.update(pos[u], pos[v], w);
    }

    /** Mode 2 **/
    inline int query(int u, int v) {
        int res = 0;
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            res += st.query(pos[head[v]], pos[v]);
        }
        if (dep[u] > dep[v]) swap(u, v);
        res += st.query(pos[u], pos[v]);
        return res;
    }


    inline void update(int u, int w) {
        st.update(pos[u], w);
    }
};