#pragma once

#include "graph/DirectedGraph.h"
#include "graph/UndirectedGraph.h"
#include "graph/WeightedDirectedGraph.h"
#include "graph/WeightedUndirectedGraph.h"

#include <sstream>
#include <string>

namespace graph {

inline std::string toDot(const UndirectedGraph& g, const std::string& name = "UndirectedGraph") {
    std::ostringstream out;
    out << "graph \"" << name << "\" {\n";
    out << "  node [shape=circle];\n";

    for (int u = 0; u < g.getNumVertices(); ++u) {
        out << "  " << u << ";\n";
    }

    for (int u = 0; u < g.getNumVertices(); ++u) {
        for (int v : g.getNeighbors(u)) {
            if (u < v) {
                out << "  " << u << " -- " << v << ";\n";
            }
        }
    }

    out << "}\n";
    return out.str();
}

inline std::string toDot(const DirectedGraph& g, const std::string& name = "DirectedGraph") {
    std::ostringstream out;
    out << "digraph \"" << name << "\" {\n";
    out << "  node [shape=circle];\n";

    for (int u = 0; u < g.getNumVertices(); ++u) {
        out << "  " << u << ";\n";
    }

    for (int u = 0; u < g.getNumVertices(); ++u) {
        for (int v : g.getNeighbors(u)) {
            out << "  " << u << " -> " << v << ";\n";
        }
    }

    out << "}\n";
    return out.str();
}

inline std::string toDot(const WeightedUndirectedGraph& g,
                         const std::string& name = "WeightedUndirectedGraph") {
    std::ostringstream out;
    out << "graph \"" << name << "\" {\n";
    out << "  node [shape=circle];\n";

    for (int u = 0; u < g.getNumVertices(); ++u) {
        out << "  " << u << ";\n";
    }

    for (int u = 0; u < g.getNumVertices(); ++u) {
        for (const auto& e : g.getEdges(u)) {
            if (u < e.to) {
                out << "  " << u << " -- " << e.to << " [label=\"" << e.weight << "\"];\n";
            }
        }
    }

    out << "}\n";
    return out.str();
}

inline std::string toDot(const WeightedDirectedGraph& g,
                         const std::string& name = "WeightedDirectedGraph") {
    std::ostringstream out;
    out << "digraph \"" << name << "\" {\n";
    out << "  node [shape=circle];\n";

    for (int u = 0; u < g.getNumVertices(); ++u) {
        out << "  " << u << ";\n";
    }

    for (int u = 0; u < g.getNumVertices(); ++u) {
        for (const auto& e : g.getEdges(u)) {
            out << "  " << u << " -> " << e.to << " [label=\"" << e.weight << "\"];\n";
        }
    }

    out << "}\n";
    return out.str();
}

}  // namespace graph
