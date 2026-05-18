#pragma once

#include "graph/Graph.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace graph {

class WeightedDirectedGraph : public Graph {
public:
    struct Edge {
        int to;
        double weight;
    };

    explicit WeightedDirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    void addEdge(int u, int v, double weight) {
        validateVertex(u);
        validateVertex(v);
        if (hasEdge(u, v)) {
            return;
        }
        adjList[u].push_back({v, weight});
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);

        auto& list = adjList[u];
        auto it = std::find_if(list.begin(), list.end(),
                               [v](const Edge& e) { return e.to == v; });
        if (it == list.end()) {
            return;
        }
        list.erase(it);
        --edgeCount;
    }

    bool hasEdge(int u, int v) const override {
        validateVertex(u);
        validateVertex(v);
        return std::find_if(adjList[u].begin(), adjList[u].end(),
                            [v](const Edge& e) { return e.to == v; }) != adjList[u].end();
    }

    double getWeight(int u, int v) const {
        validateVertex(u);
        validateVertex(v);

        for (const auto& e : adjList[u]) {
            if (e.to == v) {
                return e.weight;
            }
        }
        throw std::runtime_error("Edge does not exist");
    }

    std::vector<int> getNeighbors(int u) const override {
        validateVertex(u);
        std::vector<int> result;
        result.reserve(adjList[u].size());
        for (const auto& e : adjList[u]) {
            result.push_back(e.to);
        }
        return result;
    }

    const std::vector<Edge>& getEdges(int u) const {
        validateVertex(u);
        return adjList[u];
    }

    int getNumEdges() const override { return edgeCount; }

    int getOutDegree(int u) const {
        validateVertex(u);
        return static_cast<int>(adjList[u].size());
    }

private:
    std::vector<std::vector<Edge>> adjList;
    int edgeCount;
};

}  // namespace graph
