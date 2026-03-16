#include "locsearch.h"

TSP_task::TSP_task(int n_, double *x_, double *y_): n(n_) {
    x = new double [n];
    y = new double [n];
    for (int i = 0; i < n; i++) {
        x[i] = x_[i];
        y[i] = y_[i];
    }
}

TSP_task::~TSP_task() {
    delete [] x;
    delete [] y;
}

double TSP_task::eval(int *arr) const {
    double sum_w = 0;
    for (int i = 1; i < n; i++) {
        sum_w += sqrt((x[arr[i]] - x[arr[i - 1]]) * (x[arr[i]] - x[arr[i - 1]])
                    + (y[arr[i]] - y[arr[i - 1]]) * (y[arr[i]] - y[arr[i - 1]]));
    }
    sum_w += sqrt((x[arr[0]] - x[arr[n - 1]]) * (x[arr[0]] - x[arr[n - 1]])
                + (y[arr[0]] - y[arr[n - 1]]) * (y[arr[0]] - y[arr[n - 1]]));

    return sum_w;
}

double Solver::search(const TSP_task &t, int *init, bool use_3opt) {

    int n_attempts = sqrt(t.get_n()); // experiment

    double curr_val = t.eval(init), val = 0;
    int tmp;
    int i, j, k;
    for (int a = 0; a < n_attempts; a++) {
        i = rand() % t.get_n();
        j = rand() % t.get_n();
        k = rand() % t.get_n();

        if (use_3opt) {
            tmp = init[i];
            init[i] = init[j];
            init[j] = init[k];
            init[k] = tmp;
            val = t.eval(init);
            if (val < curr_val) {
                curr_val = val;
            }
            else {
                tmp = init[k];
                init[k] = init[j];
                init[j] = init[i];
                init[i] = tmp;
            }
        }
        else {
            tmp = init[i];
            init[i] = init[j];
            init[j] = tmp;
            val = t.eval(init);
            if (val < curr_val) {
                curr_val = val;
            }
            else {
                tmp = init[i];
                init[i] = init[j];
                init[j] = tmp;
            }
        }
    }
    

    // complete bruteforce, works too long on large tests

    // for (int i = 0; i < t.get_n(); i++) {
    //     for (int j = i + 1; j < t.get_n(); j++) {
    //         tmp = init[i];
    //         init[i] = init[j];
    //         init[j] = tmp;
    //         val = t.eval(init);
    //         if (val < curr_val) {
    //             curr_val = val;
    //         }
    //         else {
    //             tmp = init[i];
    //             init[i] = init[j];
    //             init[j] = tmp;
    //         }
    //     }
        
    // }

    if (val < curr_val) {
        return search(t, init, use_3opt);
    }
    return curr_val;
}

double Solver::solve(const TSP_task &t, int *opt_arr, bool use_3opt, int n_launches) {
    double opt_val, val = 0;
    int arr[t.get_n()];
    for (int i = 0; i < t.get_n(); i++) {
        arr[i] = -1;
    }
    int i = 0, idx;
    while (i < t.get_n()) {
        idx = rand() % t.get_n();
        if (arr[idx] == -1) {
            arr[idx] = i;
            i++;
        }
    }


    opt_val = search(t, arr, use_3opt);
    for (int i = 0; i < t.get_n(); i++) {
        opt_arr[i] = arr[i];
    }

    n_launches = sqrt(t.get_n()); //experiment

    for (int j = 0; j < n_launches; j++) {

        for (int i = 0; i < t.get_n(); i++) {
            arr[i] = -1;
        }
        i = 0;
        while (i < t.get_n()) {
            idx = rand() % t.get_n();
            if (arr[idx] == -1) {
                arr[idx] = i;
                i++;
            }
        }

        val = search(t, arr, use_3opt);

        if (val < opt_val) {
            opt_val = val;
            for (int i = 0; i < t.get_n(); i++) {
                opt_arr[i] = arr[i];
            }
        }
    }

    return opt_val;
}
