// Lowest common ancestor by binary lifting
// Ref: https://codeforces.com/blog/entry/22325
// O(N lg N) to prepare
// O(lg N) per LCA query

int dep[MAX_N], anc[MAX_LG][MAX_N];

// Call with dfs(root, root)
void dfs(int u, int p) {
    anc[0][u] = p;
    for (int i = 1; i < MAX_LG; i++)
        anc[i][u] = anc[i - 1][anc[i - 1][u]];

    for (int v : g[u]) if (v != p) {
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

int getlca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = LG - 1; i >= 0; i--)
        if (dep[v] - (1 << i) >= dep[u])
            v = anc[i][v];
    if (u == v) return u;
    for (int i = LG - 1; i >= 0; i--)
        if (anc[i][u] != anc[i][v])
            u = anc[i][u], v = anc[i][v];
    return anc[0][u];
}
