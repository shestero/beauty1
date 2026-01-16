# beauty1
Beauty server example

## How to build (Linux Debian)

* [if not done] Install C++20 compiler (in my case g++-13), Python and Conan.
* mkdir -p build
* mkdir -p conan
* conan install . --output-folder=conan --build=missing -s build_type=Release
  <br>_(In case of first use of Conan you may need initialize the profile like that:
  *conan profile detect --force*)_
* cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=conan/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-13
  <br>_(In my case I have to expicitly set compiler to g++-13 to support C++20. You may needn't do this)._
* cmake --build build -- VERBOSE=1
* ./build/beauty1

## How to build (MS Windows, using MS Visual Studio 2026 Community compiler)

* [if not done] Install MS Visual Studio with C++ and Python.
* [if not done] Install Conan:
  * py -m pip install --upgrade pip
  * py -m pip install conan
* Add path to conan.exe into PATH env
* In case of first use of Conan you may need initialize the profile like that:
  *conan profile detect --force*
* manually add to the canon profile lines:
  <br>[tool_requires]
  <br>cmake/4.2.1
  <br>_(CMake 4.2.1 is new anough to recognise MS VS 2026! You don't need this step if you have MS VS 2022)._
* in my case I had to manyally change C++ standard from 14 to 20 inside the profile.
* mkdir build conan
* conan install . --output-folder=conan --build=missing -s build_type=Release
* cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=conan\build\generators\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
* cd build
* cmake --build . --config Release
* ./Release/beauty1

## How to check

* _(From another window to check)_  curl http://localhost:8080/greet?name=Ivan
* See also: http://localhost:8080/swagger

## Running tests
* ./build/beauty1_tests
<br>or
* ctest --test-dir build --output-on-failure

