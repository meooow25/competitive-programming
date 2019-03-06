// Mo's algorithm
// Ref: https://www.hackerearth.com/practice/notes/mos-algorithm/

int N, A[MAX_N];

struct query {
    int l, r, id;
} q[MAX_Q];

inline void add() { /* do stuff */ }
inline void rem() { /* do stuff */ }

void mo() {
    int bsize = sqrt(N) + 0.5;
    auto comp = [bsize](query &q1, query &q2) {
        int b1 = q1.l / bsize, b2 = q2.l / bsize;
        return b1 != b2 ? b1 < b2 : b1 & 1 ? q1.r < q2.r : q2.r < q1.r;
    };
    sort(q, q + Q, comp);
    
    int l = 1, r = 0;
    for(int i = 0; i < Q; i++) {
        while(l < q[i].l) rem(A[l++]);
        while(l > q[i].l) add(A[--l]);
        while(r < q[i].r) add(A[++r]);
        while(r > q[i].r) rem(A[r--]);
        // Set ans[q[i].id]
    }
}
