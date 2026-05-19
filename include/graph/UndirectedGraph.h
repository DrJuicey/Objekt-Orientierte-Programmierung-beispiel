#pragma once
// Author: Person A
// Ungerichteter Graph OHNE Gewichte.
// Kanten gelten in beide Richtungen (A--B bedeutet auch B--A).

#include "Graph.h"
#include <algorithm>

namespace graph {

class UndirectedGraph : public Graph {
public:
    explicit UndirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    // Kante hinzufügen – beide Richtungen
    void addEdge(int u, int v) {
        validateVertex(u); validateVertex(v);
        if (hasEdge(u, v)) return;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u); validateVertex(v);
        erase(adjList[u], v);
        erase(adjList[v], u);
        --edgeCount;
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

    int getNumEdges()  const override { return edgeCount; }
    int getDegree(int u) const { validateVertex(u); return (int)adjList[u].size(); }

private:
    std::vector<std::vector<int>> adjList;
    int edgeCount;

    static void erase(std::vector<int>& v, int val) {
        auto it = std::find(v.begin(), v.end(), val);
        if (it != v.end()) v.erase(it);
    }
};

} // namespace graph
