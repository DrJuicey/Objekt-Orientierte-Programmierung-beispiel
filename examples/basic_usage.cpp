// Author: Person C
// Beispiel: Alle vier Graphtypen erstellen und BFS/DFS anwenden.

#include "graph/GraphAll.h"
#include <iostream>

void printVec(const std::string& label, const std::vector<int>& v) {
    std::cout << label << ": ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "=== Ungerichteter Graph (ohne Gewicht) ===\n";
    graph::UndirectedGraph ug(5);
    ug.addEdge(0,1); ug.addEdge(1,2); ug.addEdge(2,3); ug.addEdge(3,4); ug.addEdge(0,4);
    auto bfsR = graph::bfs(ug, 0);
    printVec("BFS Reihenfolge", bfsR.visitOrder);
    printVec("BFS Distanzen  ", bfsR.distance);

    std::cout << "\n=== Gerichteter Graph (ohne Gewicht) ===\n";
    graph::DirectedGraph dg(4);
    dg.addEdge(0,1); dg.addEdge(0,2); dg.addEdge(1,3); dg.addEdge(2,3);
    auto topoR = graph::topologicalSort(dg);
    printVec("Topolog. Sort  ", topoR.order);

    std::cout << "\n=== Ungerichteter Graph (mit Gewicht) ===\n";
    graph::WeightedUndirectedGraph wug(4);
    wug.addEdge(0,1,1.0); wug.addEdge(1,2,2.0); wug.addEdge(2,3,3.0); wug.addEdge(0,3,10.0);
    auto mst = graph::kruskal(wug);
    std::cout << "MST Gesamtgewicht: " << mst.totalWeight << "\n";
    for (auto& e : mst.edges)
        std::cout << "  " << e.u << "--" << e.v << " (" << e.weight << ")\n";

    std::cout << "\n=== Gerichteter Graph (mit Gewicht) ===\n";
    graph::WeightedDirectedGraph wdg(4);
    wdg.addEdge(0,1,1.0); wdg.addEdge(1,2,2.0); wdg.addEdge(0,2,10.0); wdg.addEdge(2,3,1.0);
    auto dijk = graph::dijkstra(wdg, 0);
    std::cout << "Dijkstra von Knoten 0:\n";
    for (int i = 0; i < 4; ++i)
        std::cout << "  dist[" << i << "] = " << dijk.dist[i] << "\n";
}
