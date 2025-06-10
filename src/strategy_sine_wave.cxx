#include "../include/strategy_sine_wave.hxx"
#include <cmath>

SineWaveStrategy::SineWaveStrategy() 
    : SineWaveStrategy(8.0, 100.0) {}

SineWaveStrategy::SineWaveStrategy(double freq, double amp)
    : frequency(freq), amplitude(amp), type("sine") {}

SineWaveStrategy::~SineWaveStrategy() = default;

void SineWaveStrategy::updatePoints(vtkPoints* points, int frame) {
    for (int i = 0; i < 400; ++i) {
        double x = 100 * (2 * M_PI) * static_cast<double>(i) / 400 - 100 * M_PI;
        double y = amplitude * sin((i + frame) * frequency * M_PI / 360.0);
        double z = amplitude * cos((i + frame) * frequency * M_PI / 360.0);
        points->SetPoint(i, x, y, z);
    }
}



std::string SineWaveStrategy::getType(){
    return type;
}

void SineWaveStrategy::setAmplitude(double ampl){
    amplitude = ampl;
}
