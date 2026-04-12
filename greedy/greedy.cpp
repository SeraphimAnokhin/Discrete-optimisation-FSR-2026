#include "greedy.h"

Knapsack_task::Knapsack_task(int k_, int n_, int *w_, int *v_): k(k_), n(n_) {
    w = new int [n];
    v = new int [n];
    for (int i = 0; i < n; i++) {
        w[i] = w_[i];
        v[i] = v_[i];
    }
}

Knapsack_task::Knapsack_task(const Knapsack_task &t) {
    k = t.k;
    n = t.n;
    w = new int [n];
    v = new int [n];
    for (int i = 0; i < n; i++) {
        w[i] = t.w[i];
        v[i] = t.v[i];
    }
}

Knapsack_task::~Knapsack_task() {
    delete [] w;
    delete [] v;
}

int Knapsack_task::eval(bool *arr) const {
    double sum_w = 0, sum_v = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i]) {
            sum_w += w[i];
            sum_v += v[i];
        }
    }
    return (sum_w <= k) ? sum_v : (k - sum_w);
}

double Knapsack_task::get_cal(int i) const {
    return 1.0 * v[i] / w[i];
}


int Solver::solve(const Knapsack_task &t, bool *opt_arr) {
    for (int i = 0; i < t.get_n(); i++) {
        opt_arr[i] = false;
    }

    double cal[t.get_n()];
    for (int i = 0; i < t.get_n(); i++) {
        cal[i] = t.get_cal(i);
    }

    std::vector<int> indeces;
    indeces.resize(t.get_n());
    for (int i = 0; i < t.get_n(); i++) {
        indeces[i] = i;
    }

    std::sort(indeces.begin(), indeces.end(), [&cal](int a, int b) { return cal[a] > cal[b];});
    while (cal[indeces[0]] > 0) {
        opt_arr[indeces[0]] = true;
        if (t.eval(opt_arr) < 0) {
            opt_arr[indeces[0]] = false;
        }
        cal[indeces[0]] = 0;
        std::sort(indeces.begin(), indeces.end(), [&cal](int a, int b) { return cal[a] > cal[b];});
    }

    return t.eval(opt_arr);
}
