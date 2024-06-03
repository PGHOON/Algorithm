#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <utility>
#include <limits>

using Graph = std::vector<std::vector<int>>;

class TSPAlgorithms {
public:
    static int Backtracking(const Graph &graph, std::vector<int> &best_path);
    static int BFBnB(const Graph &graph, std::vector<int> &best_path);

private:
    static void Backtrack(const Graph &graph, std::vector<int> &path, std::vector<bool> &visited, int current_length, int &min_length, std::vector<int> &best_path);
    static int Bound(const Graph &graph, const std::vector<int> &path, const std::vector<bool> &visited);
};

#endif