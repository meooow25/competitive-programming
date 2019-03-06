// Digit DP
// Counts all integers in range [0..x) with a certain property
// Ref: https://codeforces.com/blog/entry/8221

long long count(long long x) {
    stringstream ss; ss << x; string s = ss.str();
    long long ans = 0, cursum = 0;
    int n = s.size();
    int mask = 0;
    for (int i = 0; i < n; i++) {
        int cur = s[i] - '0';
        for (int d = 0; d < cur; d++) {
            // calculate dp for n - i - 1 length number
            // dp is generic with no restriction on digit choice
            // update answer
        }
        mask |= 1 << cur;
        cursum += pow10[n - i - 1] * cur % MOD;
        cursum %= MOD;
    }
    return ans;
}

// Problems:
// https://codeforces.com/contest/1073/problem/E
// More on the ref link
