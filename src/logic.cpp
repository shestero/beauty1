/**
 * @brief Business logic example: generate greeting message (implementation)
 */

#include "logic.h"
#include <format>

std::string logic(std::string_view name) {
    return std::format("Hello, {}!", name);
}
