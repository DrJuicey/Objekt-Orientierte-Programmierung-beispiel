#include "graph/GraphAll.h"
#include "graph/Graphviz.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace {

void writeFile(const std::filesystem::path& path, const std::string& content) {
    std::ofstream out(path);
    if (!out) {
        throw std::runtime_error("Failed to open output file: " + path.string());
    }
    out << content;
}

}  // namespace

int main() {
    const std::filesystem::path outputDir = "graphviz_out";
    std::filesystem::create_directories(outputDir);

    graph::UndirectedGraph ug(5);
    ug.addEdge(0, 1);
    ug.addEdge(0, 2);
    ug.addEdge(2, 3);
    ug.addEdge(3, 4);

    graph::DirectedGraph dg(5);
    dg.addEdge(0, 1);
    dg.addEdge(0, 2);
    dg.addEdge(1, 3);
    dg.addEdge(2, 4);

    graph::WeightedUndirectedGraph wug(5);
    wug.addEdge(0, 1, 2.0);
    wug.addEdge(1, 2, 1.5);
    wug.addEdge(0, 3, 4.0);
    wug.addEdge(3, 4, 2.5);

    graph::WeightedDirectedGraph wdg(5);
    wdg.addEdge(0, 1, 3.0);
    wdg.addEdge(0, 2, 1.0);
    wdg.addEdge(2, 1, 1.0);
    wdg.addEdge(1, 4, 2.0);

    writeFile(outputDir / "undirected.dot", graph::toDot(ug, "Undirected"));
    writeFile(outputDir / "directed.dot", graph::toDot(dg, "Directed"));
    writeFile(outputDir / "weighted_undirected.dot", graph::toDot(wug, "WeightedUndirected"));
    writeFile(outputDir / "weighted_directed.dot", graph::toDot(wdg, "WeightedDirected"));

    std::cout << "DOT files written to: " << outputDir << "\n";
    std::cout << "Render manually with Graphviz, for example:\n";
    std::cout << "  dot -Tsvg graphviz_out/undirected.dot -o graphviz_out/undirected.svg\n";

    return 0;
}
