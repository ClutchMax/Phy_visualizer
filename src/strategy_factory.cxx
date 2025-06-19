#include "../include/strategy_factory.hxx"
#include "../include/strategy_sine_wave.hxx"
#include "../include/strategy_random_waves.hxx"

std::unique_ptr<AnimationStrategy> StrategyFactory::create(const std::string& type, int height, int width, double param1, double param2, double param3, double param4, double param5) {
    if (type == "sine") {
        return std::make_unique<SineWaveStrategy>(height, width, param1, param2);
    } else if (type == "random_wave") {
        int duration = (int)param5;
        if(duration == 0){duration = 24;} // Prevents crashes for null duration, causing mod 0
        return std::make_unique<RandomWavesStrategy>(height, width, param1, param2, param3, param4, duration); // Example
    } //else if (type == "none") {
    //     return std::make_unique<NullStrategy>(); // Example fallback
    // **}

    return nullptr;
}