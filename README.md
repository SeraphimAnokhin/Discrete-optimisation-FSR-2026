# Discrete-optimisation-FSR-2026

Each subdirectory works as an independent project that can be compiled and launched as follows:
g++ main.cpp locsearch.h locsearch.cpp -o main
./main

## Knapsack

Input: 1st line - number of items and total capacity; each of the consequent lines - value and weight of the corresponding item.

Output: optimal sum of item values; array of ones (item is chosen) and zeros (it is not) representing the state on which that value is being reached.

## TSP

Input: 1st line - number of vertices; each of the consequent lines - cartesian coordinates (x, y) of the corresponding vertex. The graph is considered complete, i. e. each pair of vertices is connected with an edge of length equal to the distance between them.

Output: optimal route length; array of vertex numbers (optimal route).

Optional argument "3" can be used in order to use 3-opt instead of 2-opt: ./main 3.

