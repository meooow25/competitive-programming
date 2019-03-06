
bool comp[MAX_VAL];
vector<int> pr;
void eratosthenes() {
    for (int i = 2; i < MAX_VAL; i++) if (!comp[i]) {
        pr.push_back(i);
        if (1LL * i * i < MAX_VAL) for (int j = i * i; j < MAX_VAL; j += i)
            comp[j] = true;
    }
}


/** Using comp[i] **/
bool comp[MAX_VAL];
vector<int> pr;
void sieve() {
    for (int i = 2; i < MAX_VAL; i++) {
        if (!comp[i]) pr.push_back(i);
        for (int j = 0; j < pr.size() && i * pr[j] < MAX_VAL; j++) {
            comp[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
}

bool comp[MAX_VAL];
int phi[MAX_VAL];
vector<int> pr;
void sieve() {
    phi[1] = 1;
    for (int i = 2; i < MAX_VAL; i++) {
        if (!comp[i]) {
            pr.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < pr.size() && i * pr[j] < MAX_VAL; j++) {
            comp[i * pr[j]] = true;
            if (i % pr[j] == 0) {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            } else
                phi[i * pr[j]] = phi[i] * phi[pr[j]];
        }
    }
}

bool comp[MAX_VAL];
int mu[MAX_VAL];
vector<int> pr;
void sieve() {
    mu[1] = 1;
    for (int i = 2; i < MAX_VAL; i++) {
        if (!comp[i]) {
            pr.push_back(i);
            mu[i] = -1;
        }
        for (int j = 0; j < pr.size() && i * pr[j] < MAX_VAL; j++) {
            comp[i * pr[j]] = true;
            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                break;
            } else
                mu[i * pr[j]] = -mu[i];
        }
    }
}

/** Using lp[i] **/
int lp[MAX_VAL];
vector<int> pr;
void sieve() {
    for (int i = 2; i < MAX_VAL; i++) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] < MAX_VAL; j++)
            lp[i * pr[j]] = pr[j];
    }
}
