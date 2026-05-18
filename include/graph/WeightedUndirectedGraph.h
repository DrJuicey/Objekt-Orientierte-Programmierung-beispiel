#pragma once

#include "graph/Graph.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace graph {

class WeightedUndirectedGraph : public Graph {
public:
    struct Edge {
        int to;
        double weight;
    };

    explicit WeightedUndirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    void addEdge(int u, int v, double weight) {
        validateVertex(u);
        validateVertex(v);
        if (hasEdge(u, v)) {
            return;
        }
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);

        if (!hasEdge(u, v)) {
            return;
        }

        auto removeFrom = [](std::vector<Edge>& list, int target) {
            auto it = std::find_if(list.begin(), list.end(),
                                   [target](const Edge& e) { return e.to == target; });
            if (it != list.end()) {
                list.erase(it);
            }
        };

        removeFrom(adjList[u], v);
        removeFrom(adjList[v], u);
        --edgeCount;
    }

    bool hasEdge(int u, int v) const override {
        validateVertex(u);
        validateVertex(v);
        const auto& neighbors = adjList[u];
        return std::find_if(neighbors.begin(), neighbors.end(),
                            [v](const Edge& e) { return e.to == v; }) != neighbors.end();
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

private:
    std::vector<std::vector<Edge>> adjList;
    int edgeCount;
};

}  // namespace graph
