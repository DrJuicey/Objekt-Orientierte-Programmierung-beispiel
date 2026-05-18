cmake_minimum_required(VERSION 3.16)

project(GraphLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(GRAPH_BUILD_TESTS "Build tests" ON)
option(GRAPH_BUILD_EXAMPLES "Build examples" ON)

add_library(Graph STATIC src/graph.cpp)
add_library(Graph::Graph ALIAS Graph)

target_include_directories(Graph
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(Graph PUBLIC cxx_std_17)

include(GNUInstallDirs)

install(TARGETS Graph
    EXPORT GraphTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT GraphTargets
    FILE GraphTargets.cmake
    NAMESPACE Graph::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Graph
)

if(GRAPH_BUILD_EXAMPLES)
    add_executable(graph_basic_example examples/basic_usage.cpp)
    target_link_libraries(graph_basic_example PRIVATE Graph::Graph)

    add_executable(graph_graphviz_example examples/graphviz_export.cpp)
    target_link_libraries(graph_graphviz_example PRIVATE Graph::Graph)
endif()

if(GRAPH_BUILD_TESTS)
    enable_testing()
    add_executable(graph_tests tests/test_graph.cpp)
    target_link_libraries(graph_tests PRIVATE Graph::Graph)
    add_test(NAME graph_tests COMMAND graph_tests)
endif()
