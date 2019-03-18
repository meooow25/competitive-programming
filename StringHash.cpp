// Polynomial hash for strings
// hash(s) = s[0] + s[1] * b + s[2] * b^2 + ...
// Double hash

// Refs:
// https://cp-algorithms.com/string/string-hashing.html
// https://codeforces.com/blog/entry/60445
// http://codeforces.com/blog/entry/4898
// https://codeforces.com/blog/entry/60442

// Problems:
// https://www.spoj.com/problems/NHAY/

namespace StrHash {
    long long powmod(long long a, long long b, long long m) {
        long long r = 1;
        while (b) {
            if (b & 1) r = r * a % m;
            b >>= 1; a = a * a % m;
        }
        return r;
    }

    struct hpair {
        long long x, y;
        hpair(): x(0), y(0) {}
        hpair(long long x_): x(x_), y(x_) {}
        hpair(long long _x, long long _y): x(_x), y(_y) {}
        hpair operator+(const hpair &p) const { return hpair(x + p.x, y + p.y); }
        hpair operator-(const hpair &p) const { return hpair(x - p.x, y - p.y); }
        hpair operator*(const hpair &p) const { return hpair(x * p.x, y * p.y); }
        hpair operator%(const hpair &p) const { return hpair(x % p.x, y % p.y); }
        bool operator==(const hpair &p) const { return x == p.x && y == p.y; }
        bool operator!=(const hpair &p) const { return x != p.x || y != p.y; }
        bool operator<(const hpair &p) const { return x == p.x ? y < p.y : x < p.x; }
        hpair inv(const hpair &m) const {
            return hpair(powmod(x, m.x - 2, m.x), powmod(y, m.y - 2, m.y));
        }
    };
    const hpair B(257, 263), M(1e9 + 7, 1e9 + 9);

    vector<hpair> bpow, bipow;

    void init(int maxlen) {
        bpow.resize(maxlen + 1), bipow.resize(maxlen + 1);
        bpow[0] = bipow[0] = {1, 1};
        hpair binv = B.inv(M);
        for (int i = 1; i <= maxlen; i++) {
            bpow[i] = bpow[i - 1] * B % M;
            bipow[i] = bipow[i - 1] * binv % M;
        }
    }

    template <typename T>
    vector<hpair> make(const T &s, int n) {
        vector<hpair> hash(n + 1);
        for (int i = 1; i <= n; i++)
            hash[i] = (hash[i - 1] + hpair(s[i - 1]) * bpow[i - 1]) % M;
        return hash;
    }

    hpair subhash(vector<hpair> &hash, int l, int r) {
        return (hash[r + 1] - hash[l] + M) * bipow[l] % M;
    }
}
