#include "locsearch.h"

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

int Solver::search(const Knapsack_task &t, bool *init) {
    double curr_val = t.eval(init), val = 0;
    for (int i = 0; i < t.get_n(); i++) {
        init[i] = !init[i];
        val = t.eval(init);
        if (val > curr_val) {
            curr_val = val;
        }
        else {
            init[i] = !init[i];
        }
    }
    if (val > curr_val) {
        return search(t, init);
    }
    return curr_val;
}

int Solver::solve(const Knapsack_task &t, bool *opt_arr, int n_launches) {

    double opt_val, val = 0;
    bool arr[t.get_n()];
    for (int i = 0; i < t.get_n(); i++) {
        arr[i] = (rand() % 2) == 0;
    }


    opt_val = search(t, arr);
    for (int i = 0; i < t.get_n(); i++) {
        opt_arr[i] = arr[i];
    }

    n_launches = sqrt(t.get_n()); //experiment

    for (int j = 0; j < n_launches; j++) {

        for (int i = 0; i < t.get_n(); i++) {
            arr[i] = rand() % 2;
        }
        val = search(t, arr);

        if (val > opt_val) {
            opt_val = val;
            for (int i = 0; i < t.get_n(); i++) {
                opt_arr[i] = arr[i];
            }
        }
    }

    return opt_val;
}
