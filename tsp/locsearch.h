#ifndef LOCSEARCH_H
#define LOCSEARCH_H

#include <random>
#include <iostream>
#include <math.h>


class TSP_task {
    int n;
    double *x, *y;
public:
    TSP_task(int n_, double *x_, double *y_);
    ~TSP_task();
    inline int get_n() const {return n;}
    double eval(int *arr) const;
};


class Solver {
    double search(const TSP_task &t, int *init, bool use_3opt);
public:
    double solve(const TSP_task &t, int *opt_arr, bool use_3opt=false, int n_launches=10);
};



#endif
