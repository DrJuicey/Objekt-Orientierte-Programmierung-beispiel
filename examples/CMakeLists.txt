add_executable(example_basic      basic_usage.cpp)
add_executable(example_dijkstra   shortest_path.cpp)

target_link_libraries(example_basic    PRIVATE Graph)
target_link_libraries(example_dijkstra PRIVATE Graph)