#include "graph/GraphAll.h"

#include <iostream>

int main() {
    graph::WeightedUndirectedGraph g(5);
    g.addEdge(0, 1, 2.0);
    g.addEdge(1, 2, 1.5);
    g.addEdge(0, 3, 4.0);
    g.addEdge(3, 4, 2.5);

    const auto d = graph::dijkstra(g, 0);
    const auto path = graph::reconstructPath(d, 2);

    std::cout << "Distance 0->2: " << d.dist[2] << "\nPath: ";
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
    }

    graph::DirectedGraph dag(4);
    dag.addEdge(0, 1);
    dag.addEdge(1, 2);
    dag.addEdge(0, 3);

    const auto topo = graph::topologicalSort(dag);
    std::cout << "Topological sort has cycle? " << (topo.hasCycle ? "yes" : "no") << "\n";

    return 0;
}
