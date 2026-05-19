// Author: Person B
// Tests für alle Algorithmen: BFS, DFS, Dijkstra, Kruskal, TopologicalSort.

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "graph/UndirectedGraph.h"
#include "graph/DirectedGraph.h"
#include "graph/WeightedUndirectedGraph.h"
#include "graph/WeightedDirectedGraph.h"
#include "algorithms/Traversal.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/Kruskal.h"
#include "algorithms/TopologicalSort.h"

using namespace graph;

TEST_CASE("BFS: correct distances on small graph", "[bfs]") {
    UndirectedGraph g(5);
    g.addEdge(0,1); g.addEdge(1,2); g.addEdge(0,3); g.addEdge(3,4);

    auto r = bfs(g, 0);
    REQUIRE(r.distance[0] == 0);
    REQUIRE(r.distance[1] == 1);
    REQUIRE(r.distance[2] == 2);
    REQUIRE(r.distance[3] == 1);
    REQUIRE(r.distance[4] == 2);
}

TEST_CASE("BFS: shortest path reconstruction", "[bfs]") {
    UndirectedGraph g(4);
    g.addEdge(0,1); g.addEdge(1,3); g.addEdge(0,2); g.addEdge(2,3);
    auto path = bfsShortestPath(g, 0, 3);
    REQUIRE(path.front() == 0);
    REQUIRE(path.back()  == 3);
    REQUIRE(path.size()  == 3);
}

TEST_CASE("BFS: unreachable node returns -1 distance", "[bfs]") {
    UndirectedGraph g(3);
    g.addEdge(0, 1);
    auto r = bfs(g, 0);
    REQUIRE(r.distance[2] == -1);
    REQUIRE(bfsShortestPath(g, 0, 2).empty());
}

TEST_CASE("DFS: all reachable nodes visited", "[dfs]") {
    UndirectedGraph g(4);
    g.addEdge(0,1); g.addEdge(1,2); g.addEdge(2,3);
    auto r = dfs(g, 0);
    for (bool v : r.visited) REQUIRE(v);
}

TEST_CASE("isConnected: connected and disconnected graph", "[dfs]") {
    UndirectedGraph g1(3);
    g1.addEdge(0,1); g1.addEdge(1,2);
    REQUIRE(isConnected(g1));

    UndirectedGraph g2(3);
    g2.addEdge(0,1);
    REQUIRE_FALSE(isConnected(g2));
}

TEST_CASE("Dijkstra: correct shortest distances (directed)", "[dijkstra]") {
    WeightedDirectedGraph g(4);
    g.addEdge(0,1,1.0); g.addEdge(1,2,2.0); g.addEdge(0,2,10.0); g.addEdge(2,3,1.0);

    auto r = dijkstra(g, 0);
    REQUIRE_THAT(r.dist[0], Catch::Matchers::WithinAbs(0.0, 1e-9));
    REQUIRE_THAT(r.dist[1], Catch::Matchers::WithinAbs(1.0, 1e-9));
    REQUIRE_THAT(r.dist[2], Catch::Matchers::WithinAbs(3.0, 1e-9));
    REQUIRE_THAT(r.dist[3], Catch::Matchers::WithinAbs(4.0, 1e-9));
}

TEST_CASE("Dijkstra: unreachable node has infinity distance", "[dijkstra]") {
    WeightedDirectedGraph g(3);
    g.addEdge(0, 1, 5.0);
    auto r = dijkstra(g, 0);
    REQUIRE(r.dist[2] == std::numeric_limits<double>::infinity());
    REQUIRE(dijkstraPath(r, 2).empty());
}

TEST_CASE("Kruskal: MST has n-1 edges and correct weight", "[kruskal]") {
    WeightedUndirectedGraph g(4);
    g.addEdge(0,1,1.0); g.addEdge(1,2,2.0); g.addEdge(2,3,3.0); g.addEdge(0,3,10.0);

    auto r = kruskal(g);
    REQUIRE(r.edges.size() == 3);
    REQUIRE_THAT(r.totalWeight, Catch::Matchers::WithinAbs(6.0, 1e-9));
}

TEST_CASE("TopologicalSort: valid order on DAG", "[topo]") {
    DirectedGraph g(4);
    g.addEdge(0,1); g.addEdge(0,2); g.addEdge(1,3); g.addEdge(2,3);

    auto r = topologicalSort(g);
    REQUIRE_FALSE(r.hasCycle);
    REQUIRE(r.order.size() == 4);
    auto pos = [&](int v){ return std::find(r.order.begin(), r.order.end(), v) - r.order.begin(); };
    REQUIRE(pos(0) < pos(1));
    REQUIRE(pos(0) < pos(2));
    REQUIRE(pos(1) < pos(3));
    REQUIRE(pos(2) < pos(3));
}

TEST_CASE("TopologicalSort: detects cycle", "[topo]") {
    DirectedGraph g(3);
    g.addEdge(0,1); g.addEdge(1,2); g.addEdge(2,0);
    auto r = topologicalSort(g);
    REQUIRE(r.hasCycle);
}