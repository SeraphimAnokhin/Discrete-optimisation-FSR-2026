#include <iostream>
#include "locsearch.h"


int main(int argc, char **argv) {
    int n;
    std::cin >> n;
    double x[n], y[n];
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }

    bool use_3opt = false;
    if ((argc > 1) && (argv[1][0] == '3')) {
        use_3opt = true;
    }

    TSP_task t(n, x, y);
    Solver s;
    int opt_arr[n];
    std::cout << s.solve(t, opt_arr, use_3opt) << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << opt_arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
