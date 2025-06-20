#pragma once

#include "animation_strategy.hxx"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>



class RandomWavesStrategy : public AnimationStrategy {
public:
    RandomWavesStrategy();
    RandomWavesStrategy(int height, int width, double freq, double amp, double randFactor, double seed, int duration, int line_width);
    ~RandomWavesStrategy() override;
    void updateAnim(int frame) override;

    
    std::string getType() override;
    vtkSmartPointer<vtkRenderer> getRenderer(){
        return renderer;
    }


    // Class-only methods

    void setAmplitude(double ampl);
    //void addWave();
    void moveUp(int frame);
    void addLastLine(int frame);
    void generateWavePattern();
    

private:
    int height;
    int width;
    std::string type;
    double frequency;
    double amplitude;
    double random_factor;
    double seed;
    int** current_wave_pattern = nullptr;
    int duration;
    int line_width;

    vtkSmartPointer<vtkImageData> image;
    vtkSmartPointer<vtkImageActor> imgActor;
    vtkSmartPointer<vtkRenderer> renderer;

};