#include "gen.h"

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

int Knapsack_task::eval(std::vector<bool> arr) const {
    double sum_w = 0, sum_v = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i]) {
            sum_w += w[i];
            sum_v += v[i];
        }
    }
    return (sum_w <= k) ? sum_v : (k - sum_w);
}


int Solver::solve(const Knapsack_task &t, bool *opt_arr) {
    int n_generations = t.get_n();
    int population_size = t.get_n();
    int crossing_ratio = 5;
    int mutation_ratio = 10;

    std::vector<std::vector<bool>> population;
    population.resize(population_size);
    for (int i = 0; i < population_size; i++) {
        population[i].resize(t.get_n());
        for (int j = 0; j < t.get_n(); j++) {
            population[i][j] = (rand() % 2 == 0);
        }
    }

    int a, b;
    std::vector<bool> tmp;
    tmp.resize(t.get_n());
    
    for (int i = 0; i < n_generations; i++) {
        for (int j = 0; j < population_size / crossing_ratio; j++) {
            a = rand() % population_size;
            b = rand() % population_size;
            if (a == b) {
                b = (b + 1) % population_size;
            }
            
            for (int k = 0; k < t.get_n(); k++) {
                tmp[k] = (rand() % 2 == 0) ? population[a][k] : population[b][k];
            }
            population.push_back(tmp);
        }
        for (int j = 0; j < population_size / mutation_ratio; j++) {
            a = rand() % population_size;
            
            for (int k = 0; k < t.get_n(); k++) {
                tmp[k] = (rand() % mutation_ratio == 0) ? !population[a][k] : population[a][k];
            }
            population.push_back(tmp);
        }

        std::sort(population.begin(), population.end(), [&](const std::vector<bool> &a, const std::vector<bool> &b) {return t.eval(a) > t.eval(b);});
        population.resize(population_size);
    }

    for (int i = 0; i < t.get_n(); i++) {
        opt_arr[i] = population[0][i];
    }
    return t.eval(opt_arr);
}
