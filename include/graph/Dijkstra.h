#pragma once

#include "graph/WeightedDirectedGraph.h"
#include "graph/WeightedUndirectedGraph.h"

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace graph {

struct DijkstraResult {
    std::vector<double> dist;
    std::vector<int> parent;
};

inline std::vector<int> reconstructPath(const DijkstraResult& r, int end) {
    if (end < 0 || end >= static_cast<int>(r.dist.size())) {
        throw std::out_of_range("End vertex index out of range");
    }
    if (r.dist[end] == std::numeric_limits<double>::infinity()) {
        return {};
    }

    std::vector<int> path;
    for (int v = end; v != -1; v = r.parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

template <typename WeightedGraph>
inline DijkstraResult dijkstraImpl(const WeightedGraph& g, int start) {
    const int n = g.getNumVertices();
    if (start < 0 || start >= n) {
        throw std::out_of_range("Start vertex index out of range");
    }

    const double inf = std::numeric_limits<double>::infinity();
    DijkstraResult result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.dist[start] = 0.0;

    using Pair = std::pair<double, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        const auto [d, u] = pq.top();
        pq.pop();

        if (d > result.dist[u]) {
            continue;
        }

        for (const auto& e : g.getEdges(u)) {
            if (e.weight < 0.0) {
                throw std::invalid_argument("Dijkstra requires non-negative edge weights");
            }

            const double newDist = result.dist[u] + e.weight;
            if (newDist < result.dist[e.to]) {
                result.dist[e.to] = newDist;
                result.parent[e.to] = u;
                pq.push({newDist, e.to});
            }
        }
    }

    return result;
}

inline DijkstraResult dijkstra(const WeightedDirectedGraph& g, int start) {
    return dijkstraImpl(g, start);
}

inline DijkstraResult dijkstra(const WeightedUndirectedGraph& g, int start) {
    return dijkstraImpl(g, start);
}

}  // namespace graph
