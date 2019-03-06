// Heavy-light decomposition with subtree support
// https://codeforces.com/blog/entry/53170

namespace HLD {

    vector<int> par, dep, head, pos, sz;
    int cur;

    void dfs(int u, vector<int> g[]) {
        sz[u] = 1;
        for (int &v : g[u]) if (v != par[u]) {
            par[v] = u, dep[v] = dep[u] + 1;
            dfs(v, g);
            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }

    void decompose(int u, int h, vector<int> g[]) {
        pos[u] = ++cur;
        head[u] = h;
        if (g[u].empty() || g[u][0] == par[u]) return;
        decompose(g[u][0], h, g);
        for (int v : g[u]) if (v != par[u] && v != g[u][0])
            decompose(v, v, g);
    }

    void init(vector<int> g[], int n) {
        par = vector<int>(n + 1);
        dep = vector<int>(n + 1);
        sz = vector<int>(n + 1);
        pos = vector<int>(n + 1);
        head = vector<int>(n + 1);
        cur = 0;

        dfs(1, g);
        decompose(1, 1, g);
    }

    void pathstuff(int u, int v) {
        for (; head[u] != head[v]; v = par[head[v]]) {
            if (dep[head[u]] > dep[head[v]]) swap(u, v);
            // Do stuff on [pos[head[v]]..pos[v]]
        }
        if (dep[u] > dep[v]) swap(u, v);
        // Do stuff on [pos[u]..pos[v]]
    }

    void subtreestuff(int u) {
        // do stuff on [pos[u]..pos[u]+sz[u]-1]
    }

    void vertexstuff(int u) {
        // Do stuff on pos[u]
    }
}
