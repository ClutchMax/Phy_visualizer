#pragma once

#include <memory>
#include "animation_strategy.hxx"

class StrategyFactory {
public:
    static std::unique_ptr<AnimationStrategy> create(const std::string& type, int height, int width, double freq = 8.0, double amp = 100.0, double param3 = 0, double param4 = 0, double param5 = 0);
};
