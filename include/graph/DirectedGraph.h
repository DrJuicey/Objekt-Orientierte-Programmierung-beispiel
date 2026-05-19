#pragma once
// Author: Person A
// Gerichteter Graph OHNE Gewichte.
// Kante u→v bedeutet NICHT automatisch v→u.

#include "Graph.h"
#include <algorithm>

namespace graph {

class DirectedGraph : public Graph {
public:
    explicit DirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    // Kante nur in eine Richtung: u --> v
    void addEdge(int u, int v) {
        validateVertex(u); validateVertex(v);
        if (hasEdge(u, v)) return;
        adjList[u].push_back(v);
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u); validateVertex(v);
        auto& list = adjList[u];
        auto it = std::find(list.begin(), list.end(), v);
        if (it != list.end()) { list.erase(it); --edgeCount; }
    }

    bool hasEdge(int u, int v) const override {
        validateVertex(u); validateVertex(v);
        auto& nb = adjList[u];
        return std::find(nb.begin(), nb.end(), v) != nb.end();
    }

    std::vector<int> getNeighbors(int u) const override {
        validateVertex(u);
        return adjList[u];
    }

    int getNumEdges()    const override { return edgeCount; }
    int getOutDegree(int u) const { validateVertex(u); return (int)adjList[u].size(); }
    int getInDegree(int v) const {
        validateVertex(v);
        int count = 0;
        for (int u = 0; u < numVertices; ++u)
            if (hasEdge(u, v)) ++count;
        return count;
    }

    // Transponierten Graphen erstellen (alle Pfeile umkehren)
    DirectedGraph transpose() const {
        DirectedGraph t(numVertices);
        for (int u = 0; u < numVertices; ++u)
            for (int v : adjList[u])
                t.addEdge(v, u);
        return t;
    }

private:
    std::vector<std::vector<int>> adjList;
    int edgeCount;
};

} // namespace graph
