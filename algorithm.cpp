#include "algorithm.h"
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

void TSPAlgorithms::Backtrack(const Graph &graph, vector<int> &path, vector<bool> &visited, 
                              int current_length, int &min_length, vector<int> &best_path) {
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

int TSPAlgorithms::Backtracking(const Graph &graph, vector<int> &best_path) {
    int n = graph.size();
    vector<int> path = {0};
    vector<bool> visited(n, false);
    visited[0] = true;
    int min_length = numeric_limits<int>::max();
    Backtrack(graph, path, visited, 0, min_length, best_path);
    return min_length;
}

int TSPAlgorithms::Bound(const Graph &graph, const vector<int> &path, const vector<bool> &visited) {
    int n = graph.size();
    int bound = 0;

    for (size_t i = 1; i < path.size(); ++i) {
        bound += graph[path[i - 1]][path[i]];
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int min_edge = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (!visited[j] && i != j) {
                    min_edge = min(min_edge, graph[i][j]);
                }
            }
            bound += min_edge;
        }
    }

    return bound;
}

int TSPAlgorithms::BFBnB(const Graph &graph, vector<int> &best_path) {
    int n = graph.size();
    struct Node {
        vector<int> path;
        vector<bool> visited;
        int current_length;
        int bound;

        bool operator>(const Node &other) const {
            return bound > other.bound;
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    Node root = {{0}, vector<bool>(n, false), 0, 0};
    root.visited[0] = true;
    root.bound = Bound(graph, root.path, root.visited);
    pq.push(root);

    int min_length = numeric_limits<int>::max();

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        if (node.bound >= min_length) continue;

        if (node.path.size() == n) {
            int length = node.current_length + graph[node.path.back()][node.path[0]];
            if (length < min_length) {
                min_length = length;
                best_path = node.path;
                best_path.push_back(node.path[0]);
            }
        } else {
            for (int i = 0; i < n; ++i) {
                if (!node.visited[i]) {
                    Node child = node;
                    child.path.push_back(i);
                    child.visited[i] = true;
                    child.current_length += graph[node.path.back()][i];
                    child.bound = child.current_length + Bound(graph, child.path, child.visited);
                    if (child.bound < min_length) {
                        pq.push(child);
                    }
                }
            }
        }
    }

    return min_length;
}
