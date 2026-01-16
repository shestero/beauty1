# beauty1

Beauty server example

## How to build (Linux, Debian)

* **[if not done]** Install C++20 compiler (in my case g++-13), Python and Conan.
* Create directories:
  ```bash
  mkdir -p build conan
  ```
* Install dependencies with Conan:
  ```bash
  conan install . --output-folder=conan --build=missing -s build_type=Release
  ```
  _(In case of first use of Conan you may need initialize the profile like that:
  *conan profile detect --force*)_
* Configure the project with CMake:
  ```bash
  cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=conan/build/Release/generators/conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=g++-13
  ```
  _(In my case I have to explicitly set compiler to g++-13 to support C++20.
  You may not need do this)._
* Build:
  ```bash
  cmake --build build -- VERBOSE=1
  ```
* Run:
  ```bash
  ./build/beauty1
  ```

## How to build (Windows, MS Visual Studio 2026 Community)

* **[if not done]** Install MS Visual Studio with C++ and Python.
* Start **x64 Native Tools Command Prompt for VS 2026**
  (or **Developer Command Prompt for VS 2026**).
* **[if not done]** Install Conan:
  ```bat
  py -m pip install --upgrade pip
  py -m pip install conan
  ```
* Add path to **conan.exe** into PATH env var.
* In case of first use of Conan you may need initialize the profile like that:
  *conan profile detect --force*
* manually add to the Conan profile lines:
  ```ini
  [tool_requires]
  cmake/4.2.1
  ```
  _(CMake 4.2.1 is required with MS VS 2026! You don't need this step if you have MS VS 2022)._
* in my case I had to manually change C++ standard from 14 to 20 in Conan profile.
* Create directories:
  ```bat
  mkdir build conan
  ```
* Install dependencies with Conan:
  ```bat
  conan install . --output-folder=conan --build=missing -s build_type=Release
  ```
* Configure the project with CMake:
  ```bat
  cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=conan\build\generators\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
  ```
* Build:
  ```bat
  cd build
  cmake --build . --config Release
  ```
* Run:
  ```bat
  ./Release/beauty1
  ```

## How to check

* _(From another window to check)_  curl http://localhost:8080/greet?name=Ivan
* See also: http://localhost:8080/swagger

## Running tests
* ./build/beauty1_tests
<br>or
* ctest --test-dir build --output-on-failure

## Swagger dump (auto generated)
```json
{
  "openapi": "3.0.1",
  "info": {
    "title": "Beauty server example (above Boost.Beast)",
    "description": "",
    "version": ""
  },
  "paths": {
    "/": {
      "get": {
        "description": "Server's root"
      }
    },
    "/greet": {
      "get": {
        "description": "Greet a person",
        "parameters": [
          {
            "name": "name",
            "in": "get",
            "description": "The person name",
            "required": false,
            "schema": {
              "type": "string",
              "format": ""
            }
          }
        ]
      }
    },
    "/swagger": {
      "get": {
        "description": "Swagger API description entrypoint"
      }
    }
  }
}
```