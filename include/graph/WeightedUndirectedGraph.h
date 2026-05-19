#pragma once
// Author: Person A
// Ungerichteter Graph MIT Gewichten.
// Jede Kante hat ein double-Gewicht (z.B. Distanz, Kosten).

#include "Graph.h"
#include <algorithm>

namespace graph {

class WeightedUndirectedGraph : public Graph {
public:
    struct Edge { int to; double weight; };

    explicit WeightedUndirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    void addEdge(int u, int v, double weight) {
        validateVertex(u); validateVertex(v);
        if (hasEdge(u, v)) return;
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
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
        return findEdge(adjList[u], v) != adjList[u].end();
    }

    double getWeight(int u, int v) const {
        validateVertex(u); validateVertex(v);
        auto it = findEdge(adjList[u], v);
        if (it == adjList[u].end()) throw std::runtime_error("Edge does not exist");
        return it->weight;
    }

    // getNeighbors gibt nur Knoten zurück (für Graph-Interface)
    std::vector<int> getNeighbors(int u) const override {
        validateVertex(u);
        std::vector<int> result;
        for (auto& e : adjList[u]) result.push_back(e.to);
        return result;
    }

    // getEdges gibt Kanten MIT Gewicht zurück (für Algorithmen)
    const std::vector<Edge>& getEdges(int u) const {
        validateVertex(u);
        return adjList[u];
    }

    int getNumEdges() const override { return edgeCount; }

private:
    std::vector<std::vector<Edge>> adjList;
    int edgeCount;

    static std::vector<Edge>::const_iterator findEdge(const std::vector<Edge>& list, int target) {
        return std::find_if(list.begin(), list.end(),
            [target](const Edge& e){ return e.to == target; });
    }
    static void erase(std::vector<Edge>& list, int target) {
        auto it = findEdge(list, target);
        if (it != list.end()) list.erase(it);
    }
};

} // namespace graph
