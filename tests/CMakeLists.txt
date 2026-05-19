include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(test_graphs    test_graphs.cpp)
add_executable(test_algorithms test_algorithms.cpp)

target_link_libraries(test_graphs     PRIVATE Graph Catch2::Catch2WithMain)
target_link_libraries(test_algorithms PRIVATE Graph Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(test_graphs)
catch_discover_tests(test_algorithms)