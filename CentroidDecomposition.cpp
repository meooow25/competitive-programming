bool off[MAX_N];
int sz[MAX_N];

void calc_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) if (v != p && !off[v])
        calc_sz(v, u), sz[u] += sz[v];
}

int get_centroid(int u, int p, int cur_sz) {
    for (int v : g[u]) if (v != p && !off[v])
        if (sz[v] * 2 > cur_sz) return get_centroid(v, u, cur_sz);
    return u;
}

void dfs(int u, int p) {
    for (int v : g[u]) if (v != p && !off[v])
        dfs(v, u);
}

void centroid_decompose(int u) {
    calc_sz(u, u);
    int cen = get_centroid(u, u, sz[u]);
    // do stuff like dfs(cen, cen);
    off[cen] = 1;
    for (int v : g[cen]) if (!off[v])
        centroid_decompose(v);
}
