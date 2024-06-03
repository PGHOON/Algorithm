#include "algorithm.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printResult(const string &method, int(*algorithm)(const Graph&, vector<int>&), const Graph &graph) {
    vector<int> path;
    int cost;
    auto start = high_resolution_clock::now();
    cost = algorithm(graph, path);
    auto end = high_resolution_clock::now();

    cout << method << " Result:\n";
    cout << "Cost: " << cost << "\n";
    cout << "Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << "\n";
    cout << "Time: " << duration_cast<microseconds>(end - start).count() << "µs\n\n";
}

int main() {
    // adjacency matrix
    Graph graph5 = {
        {0, 5, 15, 20, 25},
        {5, 0, 35, 25, 30},
        {15, 35, 0, 30, 20},
        {20, 25, 30, 0, 15},
        {25, 30, 20, 15, 0}
    };

    // adjacency matrix
    Graph graph10 = {
        {0, 75, 80, 35, 45, 15, 45, 50, 40, 55},
        {75, 0, 65, 45, 70, 30, 10, 5, 25, 30},
        {80, 65, 0, 25, 20, 50, 55, 35, 50, 65},
        {35, 45, 25, 0, 60, 50, 30, 60, 40, 15},
        {45, 70, 20, 60, 0, 60, 85, 75, 45, 40},
        {15, 30, 50, 50, 60, 0, 55, 20, 35, 40},
        {45, 10, 55, 30, 85, 55, 0, 65, 35, 25},
        {50, 5, 35, 60, 75, 20, 65, 0, 70, 55},
        {40, 25, 50, 40, 45, 35, 35, 70, 0, 45},
        {55, 30, 65, 15, 40, 40, 25, 55, 45, 0}
    };

    /*이 경우에는 Backtracking시 0~9순서가 되어서 Backtracking이 더 빠름.
    Graph graph10 = {
        {0, 5, 10, 15, 20, 25, 30, 35, 40, 45},
        {5, 0, 15, 20, 25, 30, 35, 40, 45, 50},
        {10, 15, 0, 25, 30, 35, 40, 45, 50, 55},
        {15, 20, 25, 0, 35, 40, 45, 50, 55, 60},
        {20, 25, 30, 35, 0, 45, 50, 55, 60, 65},
        {25, 30, 35, 40, 45, 0, 55, 60, 65, 70},
        {30, 35, 40, 45, 50, 55, 0, 65, 70, 75},
        {35, 40, 45, 50, 55, 60, 65, 0, 75, 80},
        {40, 45, 50, 55, 60, 65, 70, 75, 0, 85},
        {45, 50, 55, 60, 65, 70, 75, 80, 85, 0}
    };
    */

    printResult("Backtracking (5 nodes)", TSPAlgorithms::Backtracking, graph5);
    printResult("BFBnB (5 nodes)", TSPAlgorithms::BFBnB, graph5);
    printResult("Backtracking (10 nodes)", TSPAlgorithms::Backtracking, graph10);
    printResult("BFBnB (10 nodes)", TSPAlgorithms::BFBnB, graph10);

    return 0;
}
