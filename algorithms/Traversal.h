#pragma once
// Author: Person B
// BFS (Breitensuche) und DFS (Tiefensuche).
// Beide funktionieren auf ALLEN 4 Graphtypen via Graph-Basisklasse.

#include "graph/Graph.h"
#include <vector>
#include <queue>
#include <algorithm>

namespace graph {

// ─── BFS ─────────────────────────────────────────────────────────────────────
struct BFSResult {
    std::vector<int> visitOrder; // Reihenfolge der besuchten Knoten
    std::vector<int> distance;   // Distanz vom Startknoten (-1 = nicht erreichbar)
    std::vector<int> parent;     // Vorgänger (-1 = kein)
};

inline BFSResult bfs(const Graph& g, int start) {
    int n = g.getNumVertices();
    BFSResult r;
    r.distance.assign(n, -1);
    r.parent.assign(n, -1);
    r.distance[start] = 0;

    std::queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        r.visitOrder.push_back(u);
        for (int v : g.getNeighbors(u)) {
            if (r.distance[v] == -1) {
                r.distance[v] = r.distance[u] + 1;
                r.parent[v] = u;
                q.push(v);
            }
        }
    }
    return r;
}

// Kürzester Pfad (Knotenanzahl) von start nach end
inline std::vector<int> bfsShortestPath(const Graph& g, int start, int end) {
    auto r = bfs(g, start);
    if (r.distance[end] == -1) return {}; // kein Pfad
    std::vector<int> path;
    for (int v = end; v != -1; v = r.parent[v]) path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

// ─── DFS ─────────────────────────────────────────────────────────────────────
struct DFSResult {
    std::vector<int>  visitOrder;
    std::vector<int>  parent;
    std::vector<bool> visited;
};

inline void dfsHelper(const Graph& g, int u, DFSResult& r) {
    r.visited[u] = true;
    r.visitOrder.push_back(u);
    for (int v : g.getNeighbors(u)) {
        if (!r.visited[v]) {
            r.parent[v] = u;
            dfsHelper(g, v, r);
        }
    }
}

inline DFSResult dfs(const Graph& g, int start) {
    int n = g.getNumVertices();
    DFSResult r;
    r.visited.assign(n, false);
    r.parent.assign(n, -1);
    dfsHelper(g, start, r);
    return r;
}

// Prüft ob der Graph (von start aus) zusammenhängend ist
inline bool isConnected(const Graph& g, int start = 0) {
    auto r = dfs(g, start);
    for (bool v : r.visited) if (!v) return false;
    return true;
}

} // namespace graph