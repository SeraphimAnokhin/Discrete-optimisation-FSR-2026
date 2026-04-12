#ifndef GREEDY_H
#define GREEDY_H

#include <random>
#include <iostream>
#include <vector>
#include <algorithm>


class Knapsack_task {
    int k;
    int n;
    int *w, *v;
public:
    Knapsack_task(int k_, int n_, int *w_, int *v_);
    Knapsack_task(const Knapsack_task &t);
    ~Knapsack_task();
    inline int get_n() const {return n;}
    int eval(bool *arr) const;
    double get_cal(int i) const;
};


class Solver {
public:
    int solve(const Knapsack_task &t, bool *opt_arr);
};



#endif
