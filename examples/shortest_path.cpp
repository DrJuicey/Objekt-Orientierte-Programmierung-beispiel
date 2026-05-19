// Author: Person C
// Beispiel: Dijkstra für kürzesten Weg in einem Straßennetz.
// Knoten = Städte, Kanten = Straßen mit Distanz in km.

#include "graph/GraphAll.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> cities = {"Berlin","Hamburg","Hannover","Frankfurt","München"};

    graph::WeightedUndirectedGraph g(5);
    g.addEdge(0, 1, 288.0);
    g.addEdge(0, 2, 248.0);
    g.addEdge(1, 2, 151.0);
    g.addEdge(2, 3, 357.0);
    g.addEdge(3, 4, 304.0);
    g.addEdge(2, 4, 600.0);

    int start = 0;
    int end   = 4;
    auto result = graph::dijkstra(g, start);

    std::cout << "Kürzester Weg von " << cities[start]
              << " nach " << cities[end] << ":\n";

    auto path = graph::dijkstraPath(result, end);
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << cities[path[i]];
    }
    std::cout << "\nGesamtdistanz: " << result.dist[end] << " km\n";

    std::cout << "\nAlle Distanzen von " << cities[start] << ":\n";
    for (int i = 0; i < (int)cities.size(); ++i)
        std::cout << "  " << cities[start] << " -> "
                  << cities[i] << ": " << result.dist[i] << " km\n";
}