
// Fast Fourier Transform
// Iterative Cooley-Tukey algorithm

// https://en.wikipedia.org/wiki/Fast_Fourier_transform
// https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm
// https://e-maxx-eng.appspot.com/algebra/fft.html

const double PI = acos(-1.0);

struct cplex {
    double re, im;
    cplex(double a=0., double b=0.): re(a), im(b) {}
    cplex conj() {return cplex(re, -im); }
    cplex operator+(cplex c) { return cplex(re + c.re, im + c.im); }
    cplex operator-(cplex c) { return cplex(re - c.re, im - c.im); }
    cplex operator*(double x) { return cplex(re * x, im * x); }
    cplex operator/(double x) { return cplex(re / x, im / x); }
    cplex operator*(cplex c) { return cplex(re * c.re - im * c.im, re * c.im + im * c.re); }
    cplex operator/(cplex c) { return c.conj() * *this / (c.re * c.re + c.im * c.im); }

    static const cplex ZERO, ONE, I;
};

const cplex cplex::ZERO(0.), cplex::ONE(1.), cplex::I(0., 1.);

namespace FFT {
    const int K = 15;
    const int N = 1 << K;
    vector<cplex> W, invW;
    vector<int> rev;

    void init() {
        int n2 = N >> 1;
        W.resize(n2); invW.resize(n2);
        double ang = 2 * PI / N;
        for (int i = 0; i < n2; i++)
            W[i] = cplex(cos(i * ang), sin(i * ang)), invW[i] = W[i].conj();
        rev.resize(N);
    }

    vector<int> toint(vector<cplex> a) {
        vector<int> v(a.size());
        for (int i = 0; i < a.size(); i++) v[i] = a[i].re + 0.5;
        return v;
    }

    void transform(vector<cplex> &a, bool inv=false) {
        int k = 0; while ((1 << k) < a.size()) k++;
        int n = 1 << k;
        a.resize(n, cplex::ZERO);
        rev[0] = 0;
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        vector<cplex> &twiddle = inv ? invW : W;
        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < n; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    cplex v = a[j + half] * twiddle[pw];
                    a[j + half] = a[j] - v;
                    a[j] = a[j] + v;
                    pw += diff;
                }
            }
        }

        if (inv) for (cplex &x : a) x = x / n;
    }

    void convolve(vector<cplex> &a, vector<cplex> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m, cplex::ZERO); transform(a);
        b.resize(m, cplex::ZERO); transform(b);
        for (int i = 0; i < a.size(); i++)
            a[i] = a[i] * b[i];
        transform(a, true);
        a.resize(m);
    }

    void selfconvolve(vector<cplex> &a) {
        int m = 2 * a.size() - 1;
        a.resize(m, cplex::ZERO); transform(a);
        for (int i = 0; i < a.size(); i++)
            a[i] = a[i] * a[i];
        transform(a, true);
        a.resize(m);
    }

    void transformreal(vector<cplex> &a, vector<cplex> &b) {
        int m = max(a.size(), b.size());
        vector<cplex> c(m, cplex::ZERO);
        for (int i = 0; i < a.size(); i++) c[i].re = a[i].re;
        for (int i = 0; i < b.size(); i++) c[i].im = b[i].re;
        transform(c); int n = c.size();
        a.resize(n); b.resize(n);
        a[0] = (c[0] + c[0].conj()) / 2.;
        b[0] = (c[0] - c[0].conj()) / -2. * cplex::I;
        for (int i = 1; i < n; i++) {
            a[i] = (c[i] + c[n - i].conj()) / 2.;
            b[i] = (c[i] - c[n - i].conj()) / -2. * cplex::I;
        }
    }

    void convolvereal(vector<cplex> &a, vector<cplex> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m); b.resize(m);
        transformreal(a, b);
        for (int i = 0; i < a.size(); i++)
            a[i] = a[i] * b[i];
        transform(a, true);
        a.resize(m);
    }
};