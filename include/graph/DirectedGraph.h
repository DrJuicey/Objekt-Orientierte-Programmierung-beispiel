#pragma once

#include "graph/Graph.h"

#include <algorithm>
#include <vector>

namespace graph {

class DirectedGraph : public Graph {
public:
    explicit DirectedGraph(int vertices)
        : Graph(vertices), adjList(vertices), edgeCount(0) {}

    void addEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);
        if (hasEdge(u, v)) {
            return;
        }
        adjList[u].push_back(v);
        ++edgeCount;
    }

    void removeEdge(int u, int v) {
        validateVertex(u);
        validateVertex(v);

        auto& list = adjList[u];
        auto it = std::find(list.begin(), list.end(), v);
        if (it == list.end()) {
            return;
        }
        list.erase(it);
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

    int getInDegree(int v) const {
        validateVertex(v);
        int count = 0;
        for (int u = 0; u < numVertices; ++u) {
            if (hasEdge(u, v)) {
                ++count;
            }
        }
        return count;
    }

    int getOutDegree(int u) const {
        validateVertex(u);
        return static_cast<int>(adjList[u].size());
    }

    DirectedGraph transpose() const {
        DirectedGraph t(numVertices);
        for (int u = 0; u < numVertices; ++u) {
            for (int v : adjList[u]) {
                t.addEdge(v, u);
            }
        }
        return t;
    }

private:
    std::vector<std::vector<int>> adjList;
    int edgeCount;
};

}  // namespace graph
