#include "../include/strategy_matrix_visualizer.hxx"

#include <cmath>
#include <limits>

MatrixVisualizerStrategy::MatrixVisualizerStrategy() 
    : MatrixVisualizerStrategy(500, 500, 255, 1, 96, nullptr) {}


    // TODO : INITIALIZE MATRIX
MatrixVisualizerStrategy::MatrixVisualizerStrategy(int h, int w, int range, int line_width, int anim_dur, double** matrix)
    : type("matrix_visualizer"), height(h), width(w), value_range(range), line_width(line_width), anim_duration(anim_dur) {
        image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(width, height, 1);       
        image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

        // Initialize img
        for(int i = 0 ; i < height ; i++){
            for(int j = 0 ; j < width ; j++){
                unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(j, i, 0));
                pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 255;

            }
        }

        imgActor = vtkSmartPointer<vtkImageActor>::New();
        imgActor->SetInputData(image);

        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(imgActor);
        renderer->ResetCamera();
        renderer->ResetCameraClippingRange();
    }


MatrixVisualizerStrategy::~MatrixVisualizerStrategy() = default;

void MatrixVisualizerStrategy::updateAnim(int frame){

}

