#include "../include/strategy_factory.hxx"
#include "../include/strategy_sine_wave.hxx"

std::unique_ptr<AnimationStrategy> StrategyFactory::create(const std::string& type, double param1, double param2) {
    if (type == "sine") {
        return std::make_unique<SineWaveStrategy>(param1, param2);
    } //else if (type == "spiral") {
    //     return std::make_unique<SpiralStrategy>(); // Example
    // } else if (type == "none") {
    //     return std::make_unique<NullStrategy>(); // Example fallback
    // **}

    return nullptr;
}