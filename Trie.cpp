#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e5 + 5;
const int SZ = 30;

struct Trie {
    int N, A[MAX_N];
    int trie[4][MAX_N * (SZ + 1)], cnt = 2;

    void insert(int x) {
        int cur = 1;
        for (int i = SZ - 1; i >= 0; i--) {
            trie[2][cur]++;
            int b = x >> i & 1;
            if (trie[b][cur] == 0)
                trie[b][cur] = cnt++;
            cur = trie[b][cur];
        }
        trie[2][cur]++;
        trie[3][cur] = x;
    }

    int extractmin(int x) {
        int cur = 1;
        for (int i = SZ - 1; i >= 0; i--) {
            trie[2][cur]--;
            int b = x >> i & 1;
            if (trie[b][cur] == 0 || trie[2][trie[b][cur]] == 0)
                cur = trie[!b][cur];
            else
                cur = trie[b][cur];
        }
        trie[2][cur]--;
        return x ^ trie[3][cur];
    }
};