// Basic template for a square matrix

// Problems:
// https://codeforces.com/contest/1117/problem/D

struct matrix {
    vector<vector<long long>> m;

    matrix(int n): m(n, vector<long long>(n)) {}

    static matrix identity(int n) {
        matrix m(n);
        for (int i = 0; i < n; i++)
            m.m[i][i] = 1;
        return m;
    }

    matrix operator*(const matrix &rhs) {
        assert(m.size() == rhs.m.size());
        matrix res(m.size());
        for (int i = 0; i < (int)m.size(); i++)
            for (int k = 0; k < (int)m.size(); k++)
                for (int j = 0; j < (int)m.size(); j++)
                    res.m[i][j] = (res.m[i][j] + m[i][k] * rhs.m[k][j]) % MOD;
        return res;
    }

    vector<long long> operator*(const vector<long long> &v) {
        assert(m.size() == v.size());
        vector<long long> res(v.size());
        for (int i = 0; i < (int)m.size(); i++)
            for (int j = 0; j < (int)m.size(); j++)
                res[i] = (res[i] + m[i][j] * v[j]) % MOD;
        return res;
    }

    matrix pow(long long x) {
        matrix res = identity(m.size()), a = *this;
        while (x) {
            if (x & 1) res = res * a;
            a = a * a;
            x >>= 1;
        }
        return res;
    }
};