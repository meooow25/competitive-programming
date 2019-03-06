// Generic graph stuff

// Unweighted
vector<int> g[MAX_N];

for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
}

// DFS on tree
void dfs(int u, int p) {
    for (int v : g[u]) if (v != p) {
        dfs(v, u);
    }
}

// Weighted
vector<pair<int, int >> g[MAX_N];

for (int i = 0; i < M; i++) {
    int u, v, w; cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
}

void dfs(int u, int p) {
    for (auto &vw : g[u]) if (vw.first != p) {
        int v, w; tie(v, w) = vw;
        dfs(v, u);
    }
}

// Edge problems
struct edge {
    int u, v, w;
    int other(int x) { return u ^ v ^ x; }
} ed[MAX_M];
vector<int> g[MAX_N];

for (int i = 1; i <= M; i++) {
    cin >> ed[i].u >> ed[i].v >> ed[i].w;
    g[ed[i].u].push_back(i);
    g[ed[i].v].push_back(i);
}

void dfs(int u, int up) {
    for (int e : g[u]) if (e != up) {
        int v = ed[e].other(u);
        dfs(v, e);
    }
}
