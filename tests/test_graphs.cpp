// Author: Person B
// Tests für alle vier Graphklassen.
// Getestet: addEdge, removeEdge, hasEdge, getNeighbors, Fehlerfälle.

#include <catch2/catch_test_macros.hpp>
#include "graph/UndirectedGraph.h"
#include "graph/WeightedUndirectedGraph.h"
#include "graph/DirectedGraph.h"
#include "graph/WeightedDirectedGraph.h"

using namespace graph;

TEST_CASE("UndirectedGraph: addEdge and hasEdge", "[undirected]") {
    UndirectedGraph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);

    REQUIRE(g.hasEdge(0, 1));
    REQUIRE(g.hasEdge(1, 0));
    REQUIRE_FALSE(g.hasEdge(0, 2));
    REQUIRE(g.getNumEdges() == 2);
}

TEST_CASE("UndirectedGraph: removeEdge", "[undirected]") {
    UndirectedGraph g(3);
    g.addEdge(0, 1);
    g.removeEdge(0, 1);
    REQUIRE_FALSE(g.hasEdge(0, 1));
    REQUIRE_FALSE(g.hasEdge(1, 0));
    REQUIRE(g.getNumEdges() == 0);
}

TEST_CASE("UndirectedGraph: invalid vertex throws", "[undirected]") {
    UndirectedGraph g(3);
    REQUIRE_THROWS_AS(g.addEdge(0, 5), std::out_of_range);
}

TEST_CASE("UndirectedGraph: duplicate edge ignored", "[undirected]") {
    UndirectedGraph g(3);
    g.addEdge(0, 1);
    g.addEdge(0, 1);
    REQUIRE(g.getNumEdges() == 1);
}

TEST_CASE("WeightedUndirectedGraph: weight stored correctly", "[weighted_undirected]") {
    WeightedUndirectedGraph g(3);
    g.addEdge(0, 1, 4.5);
    REQUIRE(g.hasEdge(0, 1));
    REQUIRE(g.getWeight(0, 1) == 4.5);
    REQUIRE(g.getWeight(1, 0) == 4.5);
}

TEST_CASE("WeightedUndirectedGraph: missing edge throws on getWeight", "[weighted_undirected]") {
    WeightedUndirectedGraph g(3);
    REQUIRE_THROWS_AS(g.getWeight(0, 2), std::runtime_error);
}

TEST_CASE("DirectedGraph: edge is one-directional", "[directed]") {
    DirectedGraph g(3);
    g.addEdge(0, 1);
    REQUIRE(g.hasEdge(0, 1));
    REQUIRE_FALSE(g.hasEdge(1, 0));
}

TEST_CASE("DirectedGraph: inDegree and outDegree", "[directed]") {
    DirectedGraph g(4);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    REQUIRE(g.getInDegree(2)  == 2);
    REQUIRE(g.getOutDegree(2) == 1);
}

TEST_CASE("DirectedGraph: transpose", "[directed]") {
    DirectedGraph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    auto t = g.transpose();
    REQUIRE(t.hasEdge(1, 0));
    REQUIRE(t.hasEdge(2, 1));
    REQUIRE_FALSE(t.hasEdge(0, 1));
}

TEST_CASE("WeightedDirectedGraph: basic operations", "[weighted_directed]") {
    WeightedDirectedGraph g(3);
    g.addEdge(0, 1, 3.0);
    g.addEdge(1, 2, 7.0);
    REQUIRE(g.hasEdge(0, 1));
    REQUIRE(g.getWeight(0, 1) == 3.0);
    REQUIRE_FALSE(g.hasEdge(1, 0));
    REQUIRE(g.getNumEdges() == 2);
}

TEST_CASE("Graph constructor rejects non-positive vertex count") {
    REQUIRE_THROWS_AS(UndirectedGraph(0),  std::invalid_argument);
    REQUIRE_THROWS_AS(DirectedGraph(-1),   std::invalid_argument);
}