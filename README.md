# beauty1
Beauty server example

## How to build (Linux)

* mkdir -p build
* mkdir -p conan
* conan install . --output-folder=conan --build=missing -s build_type=Release
* cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=conan/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-13
  <br>_(In my case I have to expicitly set compiler to g++-13 to support C++20. You may needn't do this)._
* cmake --build build -- VERBOSE=1
* ./build/beauty1
* _(From another window to check)_  curl http://localhost:8080/greet?name=2026

