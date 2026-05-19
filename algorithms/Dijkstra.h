#pragma once
// Author: Person B
// Dijkstra-Algorithmus: kürzeste Wege in gewichteten Graphen.
// Funktioniert NUR mit nicht-negativen Gewichten!
// Überlädt dijkstra() für beide gewichteten Graphtypen.

#include "graph/WeightedDirectedGraph.h"
#include "graph/WeightedUndirectedGraph.h"
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

namespace graph {

struct DijkstraResult {
    std::vector<double> dist;   // kürzeste Distanz von start zu jedem Knoten
    std::vector<int>    parent; // Vorgänger für Pfadrekonstruktion
};

inline std::vector<int> dijkstraPath(const DijkstraResult& r, int end) {
    const double INF = std::numeric_limits<double>::infinity();
    if (r.dist[end] == INF) return {};
    std::vector<int> path;
    for (int v = end; v != -1; v = r.parent[v]) path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

// ─── Hilfsfunktion (gemeinsamer Kern) ────────────────────────────────────────
template<typename GetEdgesFn>
DijkstraResult dijkstraImpl(int n, int start, GetEdgesFn getEdges) {
    const double INF = std::numeric_limits<double>::infinity();
    DijkstraResult r;
    r.dist.assign(n, INF);
    r.parent.assign(n, -1);
    r.dist[start] = 0.0;

    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > r.dist[u]) continue; // veralteter Eintrag
        for (const auto& e : getEdges(u)) {
            double nd = r.dist[u] + e.weight;
            if (nd < r.dist[e.to]) {
                r.dist[e.to] = nd;
                r.parent[e.to] = u;
                pq.push({nd, e.to});
            }
        }
    }
    return r;
}

inline DijkstraResult dijkstra(const WeightedDirectedGraph& g, int start) {
    return dijkstraImpl(g.getNumVertices(), start,
        [&](int u){ return g.getEdges(u); });
}

inline DijkstraResult dijkstra(const WeightedUndirectedGraph& g, int start) {
    return dijkstraImpl(g.getNumVertices(), start,
        [&](int u){ return g.getEdges(u); });
}

} // namespace graph