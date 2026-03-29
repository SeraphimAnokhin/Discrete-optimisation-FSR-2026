#ifndef BNB_H
#define BNB_H

#include <random>
#include <iostream>


class Knapsack_task {
    int k;
    int n;
    int *w, *v;
public:
    Knapsack_task(int k_, int n_, int *w_, int *v_);
    ~Knapsack_task();
    inline int get_n() const {return n;}
    int eval(bool *arr) const;
};


class Solver {
    int branch(const Knapsack_task &t, bool *opt_arr, int i);
public:
    int solve(const Knapsack_task &t, bool *opt_arr);
};



#endif
