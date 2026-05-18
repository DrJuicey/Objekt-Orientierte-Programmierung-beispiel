#include "graph/GraphAll.h"

#include <cassert>
#include <cmath>

static void testUndirectedGraph() {
    graph::UndirectedGraph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);

    assert(g.getNumEdges() == 2);
    assert(g.hasEdge(0, 1));
    assert(g.hasEdge(1, 0));
    assert(g.getDegree(1) == 2);

    g.removeEdge(0, 1);
    assert(!g.hasEdge(0, 1));
    assert(g.getNumEdges() == 1);
}

static void testWeightedDirectedDijkstra() {
    graph::WeightedDirectedGraph g(5);
    g.addEdge(0, 1, 2.0);
    g.addEdge(0, 2, 5.0);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 3, 2.0);

    const auto result = graph::dijkstra(g, 0);
    assert(std::abs(result.dist[3] - 5.0) < 1e-9);

    const auto path = graph::reconstructPath(result, 3);
    assert(path.size() == 4);
    assert(path[0] == 0 && path[1] == 1 && path[2] == 2 && path[3] == 3);
}

static void testTraversal() {
    graph::DirectedGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    const auto bfsResult = graph::bfs(g, 0);
    assert(bfsResult.distance[0] == 0);
    assert(bfsResult.distance[3] == 2);

    const auto dfsResult = graph::dfs(g, 0);
    assert(dfsResult.visited[4]);
}

static void testTopoSort() {
    graph::DirectedGraph dag(4);
    dag.addEdge(0, 1);
    dag.addEdge(1, 2);
    dag.addEdge(0, 3);

    auto topo = graph::topologicalSort(dag);
    assert(!topo.hasCycle);
    assert(topo.order.size() == 4);

    graph::DirectedGraph cyclic(2);
    cyclic.addEdge(0, 1);
    cyclic.addEdge(1, 0);

    topo = graph::topologicalSort(cyclic);
    assert(topo.hasCycle);
}

static void testKruskal() {
    graph::WeightedUndirectedGraph g(4);
    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 2.0);
    g.addEdge(2, 3, 3.0);
    g.addEdge(0, 3, 10.0);

    const auto mst = graph::kruskal(g);
    assert(mst.edges.size() == 3);
    assert(std::abs(mst.totalWeight - 6.0) < 1e-9);
}

int main() {
    testUndirectedGraph();
    testWeightedDirectedDijkstra();
    testTraversal();
    testTopoSort();
    testKruskal();
    return 0;
}
