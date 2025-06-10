#pragma once

#include <memory>
#include "animation_strategy.hxx"

class StrategyFactory {
public:
    static std::unique_ptr<AnimationStrategy> create(const std::string& type, double freq = 8.0, double amp = 100.0);
};
