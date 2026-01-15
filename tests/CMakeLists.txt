cmake_minimum_required(VERSION 3.25)

find_package(Catch2 CONFIG REQUIRED)

add_executable(beauty1_tests
        test_logic.cpp
        ../src/logic.cpp
)

target_link_libraries(beauty1_tests
        PRIVATE
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(beauty1_tests)

# Static linking just for me; I have old system libraries in my Debian 12.
target_link_options(beauty1_tests PRIVATE
        -static-libstdc++
        -static-libgcc
)
