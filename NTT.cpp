
// Number-Theoretic Transform
// Fast Fourier Transform but in the finite field of integers mod P

// https://en.wikipedia.org/wiki/Discrete_Fourier_transform_(general)#Number-theoretic_transform
// http://www.apfloat.org/ntt.html

/* various suitable primes and their generators
    786433 = 2 ^ 18 * 3 + 1, gen = 10
    7340033 = 2 ^ 20 * 7 + 1, gen = 3
    13631489 = 2 ^ 20 * 13 + 1, gen = 15
    26214401 = 2 ^ 20 * 25 + 1, gen = 3
    23068673 = 2 ^ 21 * 11 + 1, gen = 3
    69206017 = 2 ^ 21 * 33 + 1, gen = 5
    104857601 = 2 ^ 22 * 25 + 1, gen = 3
    163577857 = 2 ^ 22 * 39 + 1, gen = 23
*/

const long long MOD = 104857601;

long long powmod(long long a, int p) {
    long long r = 1;
    while (p) {
        if (p & 1) r = r * a % MOD;
        p >>= 1; a = a * a % MOD;
    }
    return r;
}

void findroot() {
    int p = MOD;
    int P = p--;
    int K = 0; while ((p & 1) == 0) p >>= 1, K++;
    int N = 1 << K;
    vector<int> pf = {2};
    for (int f = 3; f * f <= p; f++) {
        if (p % f == 0) pf.push_back(f);
        while (p % f == 0) p /= f;
    }
    if(p > 1) pf.push_back(p);
    for (int x : pf) cout << x << " "; cout << "> pf" << endl;
    int gen;
    for (gen = 2; gen < P; gen++) {
        bool ok = true;
        for (int x : pf) if (powmod(gen, (P - 1) / x) == 1) {
            ok = false; break;
        }
        if (ok) break;
    }

    cout << "gen = " << gen << endl;
    cout << "K = " << K << endl;
}

namespace NTT {
    const long long P = MOD;
    const int K = 20;
    const int GEN = 3;
    const int N = 1 << K;
    vector<int> W, invW;
    vector<int> rev;

    void init() {
        int n2 = N >> 1;
        W.resize(n2 + 1); W[0] = 1;
        W[1] = powmod(GEN, (P - 1) / N);
        for (int i = 2; i <= n2; i++)
            W[i] = 1LL * W[i - 1] * W[1] % P;
        invW.resize(n2 + 1); invW[n2] = W[n2];
        for (int i = n2 - 1; i >= 0; i--)
            invW[i] = 1LL * invW[i + 1] * W[1] % P;
        rev.resize(N);
    }

    void transform(vector<int> &a, bool inv=false) {
        int k = 0; while ((1 << k) < a.size()) k++;
        int n = 1 << k;
        a.resize(n, 0);
        rev[0] = 0;
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        vector<int> &twiddle = inv ? invW : W;
        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < n; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    int v = 1LL * a[j + half] * twiddle[pw] % P;
                    a[j + half] = a[j] - v;
                    if (a[j + half] < 0) a[j + half] += P;
                    a[j] += v;
                    if (a[j] >= P) a[j] -= P;
                    pw += diff;
                }
            }
        }

        if (inv) {
            long long inv_n = powmod(n, P - 2);
            for (int &x : a) x = x * inv_n % P;
        }
    }

    void convolve(vector<int> &a, vector<int> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m, 0); transform(a);
        b.resize(m, 0); transform(b);
        for (int i = 0; i < a.size(); i++)
            a[i] = 1LL * a[i] * b[i] % P;
        transform(a, true);
        a.resize(m);
    }

    void selfconvolve(vector<int> &a) {
        int m = 2 * a.size() - 1;
        a.resize(m, 0); transform(a);
        for (int i = 0; i < a.size(); i++)
            a[i] = 1LL * a[i] * a[i] % P;
        transform(a, true);
        a.resize(m);
    }
};