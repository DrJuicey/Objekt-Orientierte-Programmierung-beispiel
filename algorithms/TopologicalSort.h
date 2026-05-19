#pragma once
// Author: Person B
// Topologische Sortierung für gerichtete Graphen (ohne Zyklen).
// Ordnet Knoten so, dass alle Kanten "nach vorne" zeigen.
// Anwendung: Aufgabenreihenfolge mit Abhängigkeiten (z.B. Build-Systeme).

#include "graph/DirectedGraph.h"
#include <vector>
#include <stack>

namespace graph {

struct TopoResult {
    std::vector<int> order; // topologische Reihenfolge
    bool hasCycle = false;  // true = kein gültiges Ergebnis möglich
};

// DFS-basiert; color: 0=unbesucht, 1=in Bearbeitung, 2=fertig
inline bool topoHelper(const DirectedGraph& g, int u,
    std::vector<int>& color, std::stack<int>& stk)
{
    color[u] = 1;
    for (int v : g.getNeighbors(u)) {
        if (color[v] == 1) return true; // Zyklus!
        if (color[v] == 0 && topoHelper(g, v, color, stk)) return true;
    }
    color[u] = 2;
    stk.push(u);
    return false;
}

inline TopoResult topologicalSort(const DirectedGraph& g) {
    int n = g.getNumVertices();
    std::vector<int> color(n, 0);
    std::stack<int> stk;
    TopoResult result;

    for (int u = 0; u < n; ++u)
        if (color[u] == 0 && topoHelper(g, u, color, stk))
            { result.hasCycle = true; return result; }

    while (!stk.empty()) { result.order.push_back(stk.top()); stk.pop(); }
    return result;
}

} // namespace graph