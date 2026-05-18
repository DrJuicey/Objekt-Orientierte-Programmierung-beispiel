#pragma once

#include "graph/Graph.h"

#include <algorithm>
#include <queue>
#include <stdexcept>
#include <vector>

namespace graph {

struct BFSResult {
    std::vector<int> visitOrder;
    std::vector<int> distance;
    std::vector<int> parent;
};

inline void validateStart(const Graph& g, int start) {
    if (start < 0 || start >= g.getNumVertices()) {
        throw std::out_of_range("Start vertex index out of range");
    }
}

inline BFSResult bfs(const Graph& g, int start) {
    validateStart(g, start);

    const int n = g.getNumVertices();
    BFSResult result;
    result.distance.assign(n, -1);
    result.parent.assign(n, -1);

    std::queue<int> q;
    result.distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        result.visitOrder.push_back(u);

        for (int v : g.getNeighbors(u)) {
            if (result.distance[v] == -1) {
                result.distance[v] = result.distance[u] + 1;
                result.parent[v] = u;
                q.push(v);
            }
        }
    }
    return result;
}

inline std::vector<int> bfsShortestPath(const Graph& g, int start, int end) {
    validateStart(g, end);
    auto result = bfs(g, start);
    if (result.distance[end] == -1) {
        return {};
    }

    std::vector<int> path;
    for (int v = end; v != -1; v = result.parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

struct DFSResult {
    std::vector<int> visitOrder;
    std::vector<int> parent;
    std::vector<bool> visited;
};

inline void dfsHelper(const Graph& g, int u, DFSResult& result) {
    result.visited[u] = true;
    result.visitOrder.push_back(u);

    for (int v : g.getNeighbors(u)) {
        if (!result.visited[v]) {
            result.parent[v] = u;
            dfsHelper(g, v, result);
        }
    }
}

inline DFSResult dfs(const Graph& g, int start) {
    validateStart(g, start);

    const int n = g.getNumVertices();
    DFSResult result;
    result.visited.assign(n, false);
    result.parent.assign(n, -1);

    dfsHelper(g, start, result);
    return result;
}

inline bool isConnected(const Graph& g, int start = 0) {
    auto result = dfs(g, start);
    for (bool v : result.visited) {
        if (!v) {
            return false;
        }
    }
    return true;
}

}  // namespace graph
