
// Polynomial hash for strings
// hash(s) = s[0] + s[1] * b + s[2] * b^2 + ...
// Uses double hash to decrease collision chances

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
    hpair(long long _x, long long _y): x(_x), y(_y) {}
    hpair operator+(hpair p) { return hpair(x + p.x, y + p.y); }
    hpair operator-(hpair p) { return hpair(x - p.x, y - p.y); }
    hpair operator*(hpair p) { return hpair(x * p.x, y * p.y); }
    hpair operator%(hpair p) { return hpair(x % p.x, y % p.y); }
    bool operator==(hpair p) { return x == p.x && y == p.y; }
    bool operator!=(hpair p) { return x != p.x || y != p.y; }
};
const hpair B(257, 259), M(1e9 + 7, 1e9 + 9);

struct strhash {
    vector<hpair> hash, bpow, bipow;

    inline hpair inv(hpair a, hpair m) {
        return hpair(powmod(a.x, m.x - 2, m.x), powmod(a.y, m.y - 2, m.y));
    }

    strhash(char *s, int n): hash(n + 1), bpow(n + 1), bipow(n + 1) {
        bpow[0] = bipow[0] = {1, 1};
        hpair binv = inv(B, M);
        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] + hpair(s[i - 1], s[i - 1]) * bpow[i - 1]) % M;
            bpow[i] = bpow[i - 1] * B % M, bipow[i] = bipow[i - 1] * binv % M;
        }
    }

    inline hpair get(int i, int j) {
        return (hash[j + 1] - hash[i] + M) * bipow[i] % M;
    }
};

struct strhash_lowmemory {
    vector<hpair> hash;

    inline hpair inv(hpair a, hpair m) {
        return hpair(powmod(a.x, m.x - 2, m.x), powmod(a.y, m.y - 2, m.y));
    }

    strhash(char *s, int n) {
        hash.resize(n + 1);
        hpair bpow(1, 1);
        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] + hpair(s[i - 1], s[i - 1]) * bpow) % M;
            bpow = bpow * B % M;
        }
    }

    inline hpair get(int i, int j) {
        hpair bpow(powmod(B.x, i, M.x), powmod(B.y, i, M.y));
        return (hash[j + 1] - hash[i] + M) * inv(bpow, M) % M;
    }
};
