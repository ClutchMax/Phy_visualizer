#include "../include/strategy_gameOfLife.hxx"

#include <cmath>
#include <limits>
#include <stdlib.h>
#include <iostream>


GameOfLifeStrategy::GameOfLifeStrategy() 
    : GameOfLifeStrategy(900, 900, 24) {}


GameOfLifeStrategy::GameOfLifeStrategy(int h, int w, int update_freq)
    : type("game_of_life"), height(h), width(w), update_frequency(update_freq) {
        image = vtkSmartPointer<vtkImageData>::New();
        image->SetDimensions(width, height, 1);       
        image->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

        // Initialize img fond blanc
        for(int i = 0 ; i < height ; i++){
            for(int j = 0 ; j < width ; j++){
                unsigned char* pixel = static_cast<unsigned char*>(image->GetScalarPointer(j, i, 0));
                pixel[0] = 255;
                pixel[1] = 255;
                pixel[2] = 255;
            }
        }


        // Initialize game matrix and its values to 0 (no life)
        game_matrix = (int**)malloc((height/9) * sizeof(int*));
        for(int i = 0 ; i < height / 9 ; i++){
            game_matrix[i] = (int*)malloc((width / 9)* sizeof(int));
            for(int j = 0 ; j < width / 9 ; j++){
                game_matrix[i][j] = 0;
            }
        }

        // Choise of initial configuration :
        game_matrix[height / 18][width / 18] = 1;
        game_matrix[height / 18 + 1][width / 18] = 1;
        game_matrix[height / 18][width / 18 +1] = 1;
        game_matrix[height / 18 +1][width / 18 +1] = 1;
        game_matrix[height / 18 +2][width / 18] = 1;
        


        imgActor = vtkSmartPointer<vtkImageActor>::New();
        update_image();
        imgActor->SetInputData(image);

        renderer = vtkSmartPointer<vtkRenderer>::New();
        renderer->AddActor(imgActor);
        renderer->ResetCamera();
        renderer->ResetCameraClippingRange();
    }


GameOfLifeStrategy::~GameOfLifeStrategy() {
    if(game_matrix != nullptr){
        for(int i = 0 ; i < height/9 ; i++){
            free(game_matrix[i]);
        }
        free(game_matrix);
    }
}

std::string GameOfLifeStrategy::getType(){return type;}

// Naive implementation for now
void GameOfLifeStrategy::update_game_matrix() {

    int** neighbor_count = (int**)malloc(height/9 * sizeof(int*));
    for(int i = 0 ; i < height/9 ; i++){
        neighbor_count[i] = (int*)malloc(width/9 * sizeof(int));
    }

    for(int i = 0 ; i < height/9 ; i++){
        for(int j = 0 ; j < width/9 ; j++){
            neighbor_count[i][j] = 0;
            if(i > 0){
                if(j > 0 && game_matrix[i-1][j-1] == 1){neighbor_count[i][j] += 1;}
                if(game_matrix[i-1][j]== 1){neighbor_count[i][j] += 1;}
                if(j < width/9 - 1 && game_matrix[i-1][j+1] == 1){neighbor_count[i][j] += 1;}
            }

            if(j > 0 && game_matrix[i][j-1] == 1){neighbor_count[i][j] += 1;}
            if(j < width/9 - 1 && game_matrix[i][j+1] == 1){neighbor_count[i][j] += 1;}

            if(i < height / 9 - 1){
                if(j > 0 && game_matrix[i+1][j-1] == 1){neighbor_count[i][j] += 1;}
                if(game_matrix[i+1][j]== 1){neighbor_count[i][j] += 1;}
                if(j < width/9 - 1 && game_matrix[i+1][j+1] == 1){neighbor_count[i][j] += 1;}
            }
            
            
        }
        
    }

    for(int i = 0 ; i < height/9 ; i++){
        for(int j = 0 ; j < width/9 ; j++){
            if(neighbor_count[i][j] != 2 && neighbor_count[i][j] != 3){
                game_matrix[i][j] = 0;
                
                
            }

            if(neighbor_count[i][j] == 3 || (game_matrix[i][j] == 1 && neighbor_count[i][j] == 2)){
                game_matrix[i][j] = 1;
            }
        }
    }
    
    for(int i = 0 ; i < height/9 ; i++){
        free(neighbor_count[i]);
    }
    free(neighbor_count);
}


void GameOfLifeStrategy::update_image() {
    unsigned char* pixel;
    for(int i = 0 ; i < height - 1; i+=9){
        for(int j = 0 ; j < width - 1 ; j+=9){

            if(game_matrix[i/9][j/9] == 1){
                for(int a = 0 ; a < 9 ; a++){
                    for(int b = 0 ; b < 9 ; b++){
                        pixel = static_cast<unsigned char*>(image->GetScalarPointer(i+a, j+b, 0));
                        pixel[0] = 0;
                        pixel[1] = 0;
                        pixel[2] = 0;
                    }
                }
                
            } else {
                for(int a = 0 ; a < 9 ; a++){
                    for(int b = 0 ; b < 9 ; b++){
                        
                        pixel = static_cast<unsigned char*>(image->GetScalarPointer(i+a, j+b, 0));
                        pixel[0] = 255;
                        pixel[1] = 255;
                        pixel[2] = 255;
                    }
                }
            }
        }
    }
    image->Modified();
    imgActor->SetInputData(image);
    imgActor->Update();
}




void GameOfLifeStrategy::updateAnim(int frame){
    if(frame % update_frequency == 0) {
        update_game_matrix();
        update_image();
    }
}

