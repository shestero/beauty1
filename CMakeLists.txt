cmake_minimum_required(VERSION 3.25)
project(beauty1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(Boost REQUIRED COMPONENTS urls system)
find_package(beauty REQUIRED)
find_package(CLI11 REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            Boost::system
            Boost::url
            beauty::beauty
            CLI11::CLI11
)

# Static linking just for me; I have old system libraries in my Debian 12.
target_link_options(${PROJECT_NAME} PRIVATE
        -static-libstdc++
        -static-libgcc
)

