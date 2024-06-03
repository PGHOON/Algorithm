#include "algorithm.h"
#include <queue>
#include <algorithm>
#include <iostream>

void TSPAlgorithms::Backtrack(const Graph &graph, std::vector<int> &path, std::vector<bool> &visited, int current_length, int &min_length, std::vector<int> &best_path) {
    int n = graph.size();
    if (path.size() == n) {
        int length = current_length + graph[path.back()][path[0]];
        if (length < min_length) {
            min_length = length;
            best_path = path;
            best_path.push_back(path[0]);
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            Backtrack(graph, path, visited, current_length + graph[path[path.size() - 2]][i], min_length, best_path);
            visited[i] = false;
            path.pop_back();
        }
    }
}

int TSPAlgorithms::Backtracking(const Graph &graph, std::vector<int> &best_path) {
    int n = graph.size();
    std::vector<int> path = {0};
    std::vector<bool> visited(n, false);
    visited[0] = true;
    int min_length = std::numeric_limits<int>::max();
    Backtrack(graph, path, visited, 0, min_length, best_path);
    return min_length;
}

int TSPAlgorithms::Bound(const Graph &graph, const std::vector<int> &path, const std::vector<bool> &visited) {
    int n = graph.size();
    int bound = 0;

    for (size_t i = 1; i < path.size(); ++i) {
        bound += graph[path[i - 1]][path[i]];
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int min_edge = std::numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && i != j) {
                    min_edge = std::min(min_edge, graph[i][j]);
                }
            }
            bound += min_edge;
        }
    }

    return bound;
}

int TSPAlgorithms::BFBnB(const Graph &graph, std::vector<int> &best_path) {
    int n = graph.size();
    struct Node {
        std::vector<int> path;
        std::vector<bool> visited;
        int cost;
        int bound;
    };

    auto compare = [](const Node &a, const Node &b) { return a.bound > b.bound; };
    std::priority_queue<Node, std::vector<Node>, decltype(compare)> pq(compare);

    Node root;
    root.path = {0};
    root.visited = std::vector<bool>(n, false);
    root.visited[0] = true;
    root.cost = 0;
    root.bound = Bound(graph, root.path, root.visited);
    pq.push(root);

    int min_length = std::numeric_limits<int>::max();

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.bound < min_length) {
            for (int i = 0; i < n; ++i) {
                if (!node.visited[i]) {
                    Node child = node;
                    child.path.push_back(i);
                    child.visited[i] = true;
                    child.cost += graph[child.path[child.path.size() - 2]][i];

                    if (child.path.size() == n) {
                        child.cost += graph[child.path.back()][child.path[0]];
                        if (child.cost < min_length) {
                            min_length = child.cost;
                            best_path = child.path;
                            best_path.push_back(child.path[0]);
                        }
                    } else {
                        child.bound = Bound(graph, child.path, child.visited);
                        if (child.bound < min_length) {
                            pq.push(child);
                        }
                    }
                }
            }
        }
    }

    return min_length;
}