#pragma once

#include "graph/DirectedGraph.h"

#include <stack>
#include <vector>

namespace graph {

struct TopoResult {
    std::vector<int> order;
    bool hasCycle = false;
};

inline bool topoHelper(const DirectedGraph& g, int u,
                       std::vector<int>& color,
                       std::stack<int>& stack) {
    color[u] = 1;
    for (int v : g.getNeighbors(u)) {
        if (color[v] == 1) {
            return true;
        }
        if (color[v] == 0 && topoHelper(g, v, color, stack)) {
            return true;
        }
    }
    color[u] = 2;
    stack.push(u);
    return false;
}

inline TopoResult topologicalSort(const DirectedGraph& g) {
    const int n = g.getNumVertices();
    std::vector<int> color(n, 0);
    std::stack<int> stack;
    TopoResult result;

    for (int u = 0; u < n; ++u) {
        if (color[u] == 0) {
            if (topoHelper(g, u, color, stack)) {
                result.hasCycle = true;
                return result;
            }
        }
    }

    while (!stack.empty()) {
        result.order.push_back(stack.top());
        stack.pop();
    }
    return result;
}

}  // namespace graph
