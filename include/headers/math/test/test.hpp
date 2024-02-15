#pragma once

#include <functional>

#include "EngineJCoreLibs.hpp"

namespace EngineJ::math::matrix::test {
    struct Test {
        const std::string description;
        std::function<bool()> condition;
    };

    bool runTests();
}