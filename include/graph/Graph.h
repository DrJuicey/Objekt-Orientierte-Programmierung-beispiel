#pragma once
// Author: Person A
// Abstrakte Basisklasse für alle Graphtypen.
// Definiert das gemeinsame Interface (getNeighbors, hasEdge, …).

#include <vector>
#include <stdexcept>

namespace graph {

class Graph {
public:
    explicit Graph(int vertices) : numVertices(vertices) {
        if (vertices <= 0)
            throw std::invalid_argument("Number of vertices must be positive");
    }
    virtual ~Graph() = default;

    int  getNumVertices() const { return numVertices; }
    virtual int  getNumEdges()            const = 0;
    virtual bool hasEdge(int u, int v)    const = 0;
    virtual std::vector<int> getNeighbors(int u) const = 0;

protected:
    int numVertices;

    void validateVertex(int v) const {
        if (v < 0 || v >= numVertices)
            throw std::out_of_range("Vertex index out of range");
    }
};

} // namespace graph
