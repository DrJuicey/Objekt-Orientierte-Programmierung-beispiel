#include "graph/GraphAll.h"

#include <iostream>

namespace {

void printUndirectedGraph(const graph::UndirectedGraph& g) {
    std::cout << "\n=== UndirectedGraph (ungewichtet) ===\n";
    for (int u = 0; u < g.getNumVertices(); ++u) {
        std::cout << u << ": ";
        const auto neighbors = g.getNeighbors(u);
        for (std::size_t i = 0; i < neighbors.size(); ++i) {
            std::cout << neighbors[i] << (i + 1 < neighbors.size() ? ", " : "");
        }
        std::cout << "\n";
    }
}

void printDirectedGraph(const graph::DirectedGraph& g) {
    std::cout << "\n=== DirectedGraph (ungewichtet) ===\n";
    for (int u = 0; u < g.getNumVertices(); ++u) {
        std::cout << u << " -> ";
        const auto neighbors = g.getNeighbors(u);
        for (std::size_t i = 0; i < neighbors.size(); ++i) {
            std::cout << neighbors[i] << (i + 1 < neighbors.size() ? ", " : "");
        }
        std::cout << "\n";
    }
}

void printWeightedUndirectedGraph(const graph::WeightedUndirectedGraph& g) {
    std::cout << "\n=== WeightedUndirectedGraph ===\n";
    for (int u = 0; u < g.getNumVertices(); ++u) {
        std::cout << u << ": ";
        const auto& edges = g.getEdges(u);
        for (std::size_t i = 0; i < edges.size(); ++i) {
            std::cout << edges[i].to << "(" << edges[i].weight << ")"
                      << (i + 1 < edges.size() ? ", " : "");
        }
        std::cout << "\n";
    }
}

void printWeightedDirectedGraph(const graph::WeightedDirectedGraph& g) {
    std::cout << "\n=== WeightedDirectedGraph ===\n";
    for (int u = 0; u < g.getNumVertices(); ++u) {
        std::cout << u << " -> ";
        const auto& edges = g.getEdges(u);
        for (std::size_t i = 0; i < edges.size(); ++i) {
            std::cout << edges[i].to << "(" << edges[i].weight << ")"
                      << (i + 1 < edges.size() ? ", " : "");
        }
        std::cout << "\n";
    }
}

}  // namespace

int main() {
    graph::UndirectedGraph ug(5);
    ug.addEdge(0, 1);
    ug.addEdge(0, 2);
    ug.addEdge(2, 3);
    ug.addEdge(3, 4);
    printUndirectedGraph(ug);

    graph::DirectedGraph dg(5);
    dg.addEdge(0, 1);
    dg.addEdge(0, 2);
    dg.addEdge(2, 4);
    dg.addEdge(1, 3);
    printDirectedGraph(dg);

    graph::WeightedUndirectedGraph wug(5);
    wug.addEdge(0, 1, 2.0);
    wug.addEdge(1, 2, 1.5);
    wug.addEdge(0, 3, 4.0);
    wug.addEdge(3, 4, 2.5);
    printWeightedUndirectedGraph(wug);

    graph::WeightedDirectedGraph wdg(5);
    wdg.addEdge(0, 1, 3.0);
    wdg.addEdge(0, 2, 1.0);
    wdg.addEdge(2, 1, 1.0);
    wdg.addEdge(1, 4, 2.0);
    printWeightedDirectedGraph(wdg);

    const auto d = graph::dijkstra(wug, 0);
    const auto path = graph::reconstructPath(d, 2);

    std::cout << "\nDijkstra auf WeightedUndirectedGraph\n";
    std::cout << "Distance 0->2: " << d.dist[2] << "\nPath: ";
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    }

    graph::DirectedGraph dag(5);
    dag.addEdge(0, 1);
    dag.addEdge(1, 2);
    dag.addEdge(0, 3);
    dag.addEdge(3, 4);

    const auto topo = graph::topologicalSort(dag);
    std::cout << "\nTopological sort has cycle? " << (topo.hasCycle ? "yes" : "no") << "\nOrder: ";
    for (std::size_t i = 0; i < topo.order.size(); ++i) {
        std::cout << topo.order[i] << (i + 1 < topo.order.size() ? " " : "\n");
    }

    return 0;
}
