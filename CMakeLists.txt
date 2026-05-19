cmake_minimum_required(VERSION 3.15)

project(GraphLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Graph INTERFACE)
target_include_directories(Graph INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/algorithms>
    $<INSTALL_INTERFACE:.>
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:algorithms>
)

add_subdirectory(tests)
add_subdirectory(examples)

include(GNUInstallDirs)
install(TARGETS Graph EXPORT GraphTargets)
install(EXPORT GraphTargets
    FILE GraphConfig.cmake
    NAMESPACE Graph::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Graph
)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY algorithms/ DESTINATION algorithms)
