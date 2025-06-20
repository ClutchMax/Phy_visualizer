#include "../include/strategy_random_waves.hxx"

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <limits>
#include <vtkTransform.h>
#include <vtkImageReslice.h>

RandomWavesStrategy::RandomWavesStrategy()
    : RandomWavesStrategy(500, 800, .0, .0, .0, .0, 24, 3) {}

RandomWavesStrategy::RandomWavesStrategy(int height, int width, double freq, double amp, double randFactor, double seed, int duration, int line_width)
    : height(height), width(width), frequency(freq), amplitude(amp), type("random_wave"), random_factor(randFactor), seed(seed), duration(duration), line_width(line_width) {

        image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(width, height, 1);       
        image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

        // Initialize img
        for(int i = 0 ; i < height ; i++){
            for(int j = 0 ; j < width ; j++){
                unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(j, i, 0));
                // Grey scale by height
                // pixel[0] = i*255/height;
                // pixel[1] = i*255/height;
                // pixel[2] = i*255/height;
                pixel[0] = 121;
                pixel[1] = 214;
                pixel[2] = 247;

            }
        }

    

        imgActor = vtkSmartPointer<vtkImageActor>::New();
        imgActor->SetInputData(image);

        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(imgActor);
        renderer->ResetCamera();
        renderer->ResetCameraClippingRange();

    }

RandomWavesStrategy::~RandomWavesStrategy() {
    if(current_wave_pattern != nullptr){
        for(int x = 0 ; x < (int)amplitude *2 +1 ; ++x){
            free(current_wave_pattern[x]);
        } 
        free(current_wave_pattern);
    }
}



void RandomWavesStrategy::moveUp(int frame){
    auto reslice = vtkSmartPointer<vtkImageReslice>::New();
    reslice->SetInputData(image);

    // Shift transform: translate by (0, -1, 0) pixels
    auto transform = vtkSmartPointer<vtkTransform>::New();
    transform->Translate(0, -1, 0);

    reslice->SetResliceTransform(transform);
    reslice->Update();

    image = reslice->GetOutput();
    addLastLine(frame);

    imgActor->SetInputData(image);
    imgActor->Update();
}


void RandomWavesStrategy::addLastLine(int frame){

    if(current_wave_pattern == nullptr){
        std::cout << "Skipping addLastLine cause no pattern was given." << std::endl;
        return;
    }

    int index_to_add = frame % duration;
    int ampl_int = (int) floor(amplitude); 
    if(index_to_add > 2*ampl_int + 1){return;} // We've already printed the whole sine

    int* row_to_add = current_wave_pattern[index_to_add];

    // Apply on image
    const int width = image->GetDimensions()[0];
    for(int x = 0 ; x < width ; ++x){
        unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(x, 0, 0));
        if(row_to_add[x] != 1){
            // Keep background color
            pixel[0] = 121;
            pixel[1] = 214;
            pixel[2] = 247;
        } else {
            // Print white sine
            pixel[0] = 255;
            pixel[1] = 255;
            pixel[2] = 255;
        }
    }
}



// generate the wave function that will be printed from top to bottom during the animation, and 
// puts it in the "current_wave_pattern" member
void RandomWavesStrategy::generateWavePattern(){

    const int width = image->GetDimensions()[0];
    const int height = image->GetDimensions()[1];
    const double phaseSpeed = 0.0;

    int ampl_int = (int) floor(amplitude); 
    int** sin_matrix = current_wave_pattern;

    
    // First call initializes the matrix
    if(sin_matrix == nullptr){
        sin_matrix = (int**)malloc((ampl_int*2 +1) * sizeof(int*));
        for(int x = 0 ; x < (ampl_int*2 +1) ; x++){
            sin_matrix[x] = (int*)malloc(width * sizeof(int));
        }
    } 

    
    // Resets value of the matrix
    for(int x = 0 ; x < (ampl_int*2 +1) ; x++){
        for(int y = 0 ; y < width ; y++){
            sin_matrix[x][y] = INT_MIN;
        }
    } 


    // Calculate new values
    for(int x = 0 ; x < width ; x++){
        double tmp = 8*sin(x/10) - 4*sin(x/6) + 9*sin(x/8 + M_PI/4.0);
        //double tmp = sin(x/10);
        int y = (int)round(tmp);
        if(y > (-ampl_int) && y <= (ampl_int)){
            sin_matrix[y+ampl_int][x] = 1;

            // Adds width to the line (if line_width > 1)
            for(int i = 0 ; i < line_width ; i++){
                if(y - i > (-ampl_int)){sin_matrix[y+ampl_int-i][x] = 1;}
                if(y + i > (-ampl_int)){sin_matrix[y+ampl_int+i][x] = 1;}
            }
        }        
    }

    current_wave_pattern = sin_matrix;
    

}



void RandomWavesStrategy::updateAnim(int frame){

    if(frame % duration == 0){
        generateWavePattern();
    } 
    
    moveUp(frame);
    image->Modified();
    
}




std::string RandomWavesStrategy::getType(){return type;}

void RandomWavesStrategy::setAmplitude(double ampl){
    amplitude = ampl;
}


void initialize_image_grey_scalar (){
    
}

void print_matrix(int** mat, int n, int m){
    std::cout << "[";
    for(int x = 0 ; x < n ; x++){
        for(int y = 0 ; y < m ; y++){
            std::cout << mat[x][y]; 
        }
        std::cout << std::endl;
    } 
    std::cout << "]" << std::endl;
}