#pragma once

#include "graph/Graph.h"

#include <algorithm>
#include <vector>

namespace graph {

class UndirectedGraph : public Graph {
public:
    explicit UndirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    void addEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);
        if (hasEdge(u, v)) {
            return;
        }
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);

        auto& lu = adjList[u];
        auto& lv = adjList[v];

        auto itu = std::find(lu.begin(), lu.end(), v);
        auto itv = std::find(lv.begin(), lv.end(), u);
        if (itu == lu.end() || itv == lv.end()) {
            return;
        }

        lu.erase(itu);
        lv.erase(itv);
        --edgeCount;
    }

    bool hasEdge(int u, int v) const override {
        validateVertex(u);
        validateVertex(v);
        const auto& neighbors = adjList[u];
        return std::find(neighbors.begin(), neighbors.end(), v) != neighbors.end();
    }

    std::vector<int> getNeighbors(int u) const override {
        validateVertex(u);
        return adjList[u];
    }

    int getNumEdges() const override { return edgeCount; }

    int getDegree(int u) const {
        validateVertex(u);
        return static_cast<int>(adjList[u].size());
    }

private:
    std::vector<std::vector<int>> adjList;
    int edgeCount;
};

}  // namespace graph
