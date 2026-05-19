#pragma once
// Author: Person B
// Kruskal-Algorithmus: Minimaler Spannbaum (MST) für gewichtete ungerichtete Graphen.
// Idee: Kanten nach Gewicht sortieren, kleinste zuerst hinzufügen
//       solange kein Zyklus entsteht (Union-Find Datenstruktur).

#include "graph/WeightedUndirectedGraph.h"
#include <vector>
#include <algorithm>

namespace graph {

// Union-Find mit Pfadkompression
struct UnionFind {
    std::vector<int> parent, rank;
    explicit UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return false; // würde Zyklus erzeugen
        if (rank[pu] < rank[pv]) std::swap(pu, pv);
        parent[pv] = pu;
        if (rank[pu] == rank[pv]) ++rank[pu];
        return true;
    }
};

struct KruskalResult {
    struct MSTEdge { int u, v; double weight; };
    std::vector<MSTEdge> edges; // Kanten des MST
    double totalWeight = 0.0;
};

inline KruskalResult kruskal(const WeightedUndirectedGraph& g) {
    int n = g.getNumVertices();

    // Alle Kanten einmal sammeln (u < v verhindert Duplikate)
    struct RawEdge { int u, v; double w; };
    std::vector<RawEdge> all;
    for (int u = 0; u < n; ++u)
        for (auto& e : g.getEdges(u))
            if (u < e.to) all.push_back({u, e.to, e.weight});

    std::sort(all.begin(), all.end(), [](const RawEdge& a, const RawEdge& b){ return a.w < b.w; });

    UnionFind uf(n);
    KruskalResult result;
    for (auto& e : all) {
        if (uf.unite(e.u, e.v)) {
            result.edges.push_back({e.u, e.v, e.w});
            result.totalWeight += e.w;
            if ((int)result.edges.size() == n - 1) break; // MST vollständig
        }
    }
    return result;
}

} // namespace graph