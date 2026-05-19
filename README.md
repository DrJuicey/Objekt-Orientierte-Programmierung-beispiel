# Kleine Graphen Bibliothek (C++)

Diese Repository-Struktur passt zum OOP-Projekt (WiSe 2025/2026) mit:

- Bibliothek fuer 4 Graph-Typen (gerichtet/ungerichtet, gewichtet/ungewichtet)
- Algorithmen fuer Traversal, kuerzeste Wege, MST und Topological Sort
# Kleine Graphen Bibliothek (C++)

OOP-Projekt WiSe 2025/2026 · Gruppe [Nummer eintragen]

## Projektstruktur

```
graph-library/
├── include/graph/          # Graphklassen  (Person A)
│   ├── Graph.h             #   Basisklasse
│   ├── UndirectedGraph.h
│   ├── WeightedUndirectedGraph.h
│   ├── DirectedGraph.h
│   ├── WeightedDirectedGraph.h
│   └── GraphAll.h          #   Master-Include
├── algorithms/             # Algorithmen   (Person B)
│   ├── Traversal.h         #   BFS, DFS
│   ├── Dijkstra.h
│   ├── Kruskal.h
│   └── TopologicalSort.h
├── tests/                  # Tests         (Person B)
│   ├── test_graphs.cpp
│   ├── test_algorithms.cpp
│   └── CMakeLists.txt
├── examples/               # Beispiele     (Person C)
│   ├── basic_usage.cpp
│   ├── shortest_path.cpp
│   └── CMakeLists.txt
├── CMakeLists.txt
└── README.md
```

## Abgedeckte Graph-Typen

| Klasse                   | Gerichtet | Gewichtet |
|--------------------------|-----------|-----------|
| `UndirectedGraph`        | Nein      | Nein      |
| `WeightedUndirectedGraph`| Nein      | Ja        |
| `DirectedGraph`          | Ja        | Nein      |
| `WeightedDirectedGraph`  | Ja        | Ja        |

## Implementierte Algorithmen

| Algorithmus         | Datei                | Graphtypen                          |
|---------------------|----------------------|-------------------------------------|
| BFS / DFS           | `Traversal.h`        | alle (via Basisklasse)              |
| Dijkstra            | `Dijkstra.h`         | gewichtete gerichtete + ungerichtete|
| Kruskal (MST)       | `Kruskal.h`          | gewichteter ungerichteter           |
| Topolog. Sortierung | `TopologicalSort.h`  | gerichteter ungewichteter           |

## Teamaufteilung (3 Personen)

| Person   | Branch              | Zuständigkeit                   |
|----------|---------------------|---------------------------------|
| Person A | `feature/graphs`    | `include/graph/` — Graphklassen |
| Person B | `feature/algos`     | `algorithms/` + `tests/`        |
| Person C | `feature/examples`  | `examples/` + `README.md`       |

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Beispiele ausführen

```bash
./build/example_basic
./build/example_dijkstra
```

## In ein anderes CMake-Projekt einbinden

```cmake
find_package(Graph REQUIRED)
target_link_libraries(MeinProjekt PRIVATE Graph::Graph)
```

Oder als Subprojekt:

```cmake
add_subdirectory(graph-library)
target_link_libraries(MeinProjekt PRIVATE Graph)
```
- `graphviz_out/weighted_undirected.dot`
