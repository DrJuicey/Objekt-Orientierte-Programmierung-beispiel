# Kleine Graphen Bibliothek (C++)

Diese Repository-Struktur passt zum OOP-Projekt (WiSe 2025/2026) mit:

- Bibliothek fuer 4 Graph-Typen (gerichtet/ungerichtet, gewichtet/ungewichtet)
- Algorithmen fuer Traversal, kuerzeste Wege, MST und Topological Sort
- CMake-Build fuer Library, Tests, Beispiele

## Projektstruktur

```
.
|-- CMakeLists.txt
|-- include/graph/
|   |-- Graph.h
|   |-- UndirectedGraph.h
|   |-- WeightedUndirectedGraph.h
|   |-- DirectedGraph.h
|   |-- WeightedDirectedGraph.h
|   |-- Traversal.h
|   |-- Dijkstra.h
|   |-- Kruskal.h
|   |-- TopologicalSort.h
|   `-- GraphAll.h
|-- src/graph.cpp
|-- tests/test_graph.cpp
`-- examples/basic_usage.cpp
```

## Abgedeckte Graph-Typen

1. `DirectedGraph` (ungerichtet: nein, gewichtet: nein)
2. `UndirectedGraph` (ungerichtet: ja, gewichtet: nein)
3. `WeightedDirectedGraph` (ungerichtet: nein, gewichtet: ja)
4. `WeightedUndirectedGraph` (ungerichtet: ja, gewichtet: ja)

## Implementierte Algorithmen und Abdeckung

1. BFS/DFS (`Traversal.h`): alle Typen (ueber `Graph`-Interface)
2. Dijkstra (`Dijkstra.h`): gewichtete gerichtete und ungerichtete Graphen
3. Kruskal (`Kruskal.h`): gewichtete ungerichtete Graphen
4. Topological Sort (`TopologicalSort.h`): gerichtete Graphen

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Beispiel ausfuehren

```bash
./build/graph_basic_example
```

## Einbindung in andere CMake-Projekte

Library kann installiert und danach als Target verwendet werden:

```bash
cmake -S . -B build
cmake --build build
cmake --install build --prefix install
```

Danach kann in einem externen Projekt `find_package(Graph)` und `target_link_libraries(... Graph::Graph)` genutzt werden.
