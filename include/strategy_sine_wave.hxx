#pragma once

#include "animation_strategy.hxx"

class SineWaveStrategy : public AnimationStrategy {
public:
    SineWaveStrategy();
    SineWaveStrategy(double freq, double amp);
    ~SineWaveStrategy() override;
    void updatePoints(vtkPoints* points, int frame) override;

    
    std::string getType() override;


    // Class-only methods

    void setAmplitude(double ampl);

private:
    std::string type;
    double frequency;
    double amplitude;
};