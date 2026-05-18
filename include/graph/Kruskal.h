#pragma once

#include "graph/WeightedUndirectedGraph.h"

#include <algorithm>
#include <vector>

namespace graph {

struct UnionFind {
    std::vector<int> parent;
    std::vector<int> rank;

    explicit UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) {
            return false;
        }
        if (rank[pu] < rank[pv]) {
            std::swap(pu, pv);
        }
        parent[pv] = pu;
        if (rank[pu] == rank[pv]) {
            ++rank[pu];
        }
        return true;
    }
};

struct KruskalResult {
    struct MSTEdge {
        int u;
        int v;
        double weight;
    };

    std::vector<MSTEdge> edges;
    double totalWeight = 0.0;
};

inline KruskalResult kruskal(const WeightedUndirectedGraph& g) {
    const int n = g.getNumVertices();

    struct RawEdge {
        int u;
        int v;
        double w;
    };

    std::vector<RawEdge> allEdges;
    for (int u = 0; u < n; ++u) {
        for (const auto& e : g.getEdges(u)) {
            if (u < e.to) {
                allEdges.push_back({u, e.to, e.weight});
            }
        }
    }

    std::sort(allEdges.begin(), allEdges.end(),
              [](const RawEdge& a, const RawEdge& b) { return a.w < b.w; });

    UnionFind uf(n);
    KruskalResult result;

    for (const auto& e : allEdges) {
        if (uf.unite(e.u, e.v)) {
            result.edges.push_back({e.u, e.v, e.w});
            result.totalWeight += e.w;
        }
        if (static_cast<int>(result.edges.size()) == n - 1) {
            break;
        }
    }

    return result;
}

}  // namespace graph
