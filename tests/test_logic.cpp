#include <catch2/catch_test_macros.hpp>
#include <string>

std::string logic(std::string_view name);

TEST_CASE("Greeting logic works") {
REQUIRE(logic("Mike") == "Hello, Mike!");
REQUIRE(logic("2026") == "Hello, 2026!");
}
