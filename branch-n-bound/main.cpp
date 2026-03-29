#include <iostream>
#include "bnb.h"


int main(int argc, char **argv) {
    int n, k;
    std::cin >> n >> k;
    int v[n], w[n];

    for (int i = 0; i < n; i++) {
        std::cin >> v[i] >> w[i];
    }
    
    Knapsack_task t(k, n, w, v);
    Solver s;
    bool opt_arr[n];
    
    std::cout << s.solve(t, opt_arr) << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << opt_arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
