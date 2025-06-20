#pragma once

#include "animation_strategy.hxx"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>

class GameOfLifeStrategy : public AnimationStrategy {
public:
    GameOfLifeStrategy();
    GameOfLifeStrategy(int h, int w, int update_freq);
    ~GameOfLifeStrategy() override;
    void updateAnim(int frame) override;

    void update_game_matrix();
    void update_image();


    std::string getType() override;
    vtkSmartPointer<vtkRenderer> getRenderer(){
        return renderer;
    }


private:
    int height;
    int width;
    std::string type;
    int update_frequency;
    int** game_matrix;

    vtkSmartPointer<vtkImageData> image;
    vtkSmartPointer<vtkImageActor> imgActor;
    vtkSmartPointer<vtkRenderer> renderer;
};