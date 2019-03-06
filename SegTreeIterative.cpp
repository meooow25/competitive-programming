struct SegTree {
    int n;
    vector<int> tree;

    SegTree(int n_) {
        n = 1; while (n < n_) n <<= 1;
        tree.resize(n << 1);
    }

    /**   Mode 1   **/
    void update(int i, int v) {
        tree[i + n] = v;
        for(i = (i + n) >> 1; i > 0; i >>= 1)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    
    int query(int i, int j) {
        int v = 0;
        for (i += n, j += n; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if ((i & 1) == 1) v += tree[i];
            if ((j & 1) == 0) v += tree[j];
        }
        return v;
    }

    /**   Mode 2   **/
    void update(int i, int j, int v) {
        for (i += n, j += n; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if((i & 1) == 1) tree[i] += v;
            if((j & 1) == 0) tree[j] += v;
        }
    }

    int query(int i) {
        int v = 0;
        for(i += n; i > 0; i >>= 1)
            v += tree[i];
        return v;
    }
};
