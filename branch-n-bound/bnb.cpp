#include "bnb.h"

Knapsack_task::Knapsack_task(int k_, int n_, int *w_, int *v_): k(k_), n(n_) {
    w = new int [n];
    v = new int [n];
    for (int i = 0; i < n; i++) {
        w[i] = w_[i];
        v[i] = v_[i];
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

int Solver::branch(const Knapsack_task &t, bool *opt_arr, int i) {
    if (i >= t.get_n()) {
        return t.eval(opt_arr);
    }
    if (t.eval(opt_arr) < 0) {
        return -1;
    }

    double val1 = branch(t, opt_arr, i + 1);
    opt_arr[i] = !opt_arr[i];
    double val2 = branch(t, opt_arr, i + 1);

    if (val1 > val2) {
        opt_arr[i] = !opt_arr[i];
        return val1;
    }
    return val2;
}

int Solver::solve(const Knapsack_task &t, bool *opt_arr) {
    for (int i = 0; i < t.get_n(); i++) {
        opt_arr[i] = false;
    }
    return branch(t, opt_arr, 0);
}
