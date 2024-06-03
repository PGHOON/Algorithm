#include "algorithm.h"
#include <iostream>
#include <vector>
#include <chrono>

void PrintResult(const std::string &method, int cost, const std::vector<int> &path) {
    std::cout << method << " Result:\n";
    std::cout << "Cost: " << cost << "\n";
    std::cout << "Path: ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << "\n";
}

int main() {
    Graph graph5 = {
        {0, 2, 9, 10, 1},
        {1, 0, 6, 4, 1},
        {15, 7, 0, 8, 3},
        {6, 3, 12, 0, 4},
        {3, 6, 8, 4, 0}
    };

    Graph graph10 = {
        {0, 29, 20, 21, 16, 31, 100, 12, 4, 31},
        {29, 0, 15, 29, 28, 40, 72, 21, 29, 41},
        {20, 15, 0, 15, 14, 25, 81, 9, 23, 27},
        {21, 29, 15, 0, 4, 12, 92, 12, 25, 13},
        {16, 28, 14, 4, 0, 16, 94, 9, 20, 16},
        {31, 40, 25, 12, 16, 0, 95, 24, 36, 3},
        {100, 72, 81, 92, 94, 95, 0, 90, 101, 99},
        {12, 21, 9, 12, 9, 24, 90, 0, 15, 25},
        {4, 29, 23, 25, 20, 36, 101, 15, 0, 35},
        {31, 41, 27, 13, 16, 3, 99, 25, 35, 0}
    };

    std::vector<int> path;
    int cost;

    auto start = std::chrono::high_resolution_clock::now();
    cost = TSPAlgorithms::Backtracking(graph5, path);
    auto end = std::chrono::high_resolution_clock::now();
    PrintResult("Backtracking (5 nodes)", cost, path);
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    cost = TSPAlgorithms::Backtracking(graph10, path);
    end = std::chrono::high_resolution_clock::now();
    PrintResult("Backtracking (10 nodes)", cost, path);
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    cost = TSPAlgorithms::BFBnB(graph5, path);
    end = std::chrono::high_resolution_clock::now();
    PrintResult("BFBnB (5 nodes)", cost, path);
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    start = std::chrono::high_resolution_clock::now();
    cost = TSPAlgorithms::BFBnB(graph10, path);
    end = std::chrono::high_resolution_clock::now();
    PrintResult("BFBnB (10 nodes)", cost, path);
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    return 0;
}
