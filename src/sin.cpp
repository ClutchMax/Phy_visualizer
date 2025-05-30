#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkCommand.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

#include <wx/wx.h>
#include <math.h>
#include <iostream>
#include <thread>

struct point3d {
    double x;
    double y;
    double z;
};



int main(int, char*[])
{
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkPoints> points;
    // Create five points.
    // double origin[3] = {0.0, 0.0, 0.0};
    // double p0[3] = {1.0, 0.0, 0.0};
    // double p1[3] = {0.0, 1.0, 0.0};
    // double p2[3] = {0.0, 1.0, 2.0};
    // double p3[3] = {1.0, 2.0, 3.0};

    for(int x = 0 ; x < 400; x++){
        double tmp[3] = {1000*(2*M_PI)*(double)x/400 - M_PI, 100 * sin(x * 8 * M_PI / 360), 0};
        std::cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << endl;
        points->InsertNextPoint(tmp);
    }

    // Create a vtkPoints object and store the points in it.
    
   

    vtkNew<vtkPolyLine> polyLine;
    polyLine->GetPointIds()->SetNumberOfIds(400);
    for (unsigned int i = 0; i < 400; i++)
    {
        polyLine->GetPointIds()->SetId(i, i);
    }

    // Create a cell array to store the lines in and add the lines to it.
    vtkNew<vtkCellArray> cells;
    cells->InsertNextCell(polyLine);

    // Create a polydata to store everything in.
    vtkNew<vtkPolyData> polyData;

    // Add the points to the dataset.
    polyData->SetPoints(points);

    // Add the lines to the dataset.
    polyData->SetLines(cells);

    // Setup actor and mapper.
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputData(polyData);

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());

    // Setup render window, renderer, and interactor.
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetWindowName("PolyLine");
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1000, 500);

    vtkNew<vtkWindowToImageFilter> windowToImageFilter;
    windowToImageFilter->SetInput(renderWindow);
    windowToImageFilter->SetInputBufferTypeToRGBA(); // To capture color + alpha
    windowToImageFilter->ReadFrontBufferOff();       // Offscreen rendering


    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("Black").GetData());
    //renderer->GetActiveCamera()->SetParallelProjection(true);
    //renderer->GetActiveCamera()->SetParallelScale(100);

    vtkCamera* cam = renderer->GetActiveCamera();
    
    cam->SetPosition(0, -500, 1000);           // 2e coord : distance avec l'objet
    cam->SetFocalPoint(0, 0, 0);
    cam->SetViewUp(0, 1, 0);
    
    renderer->ResetCameraClippingRange();
    
   

    int frame = 0;

    while (frame < 360) {
        for (int i = 0; i < 400; i++) {
            double x = 100 * (2 * M_PI) * static_cast<double>(i) / 400 - 100 * M_PI;
            double y = 100 * sin((i + frame) * 8 * M_PI / 360.0);
            double z = 100 * cos((i + frame) * 8 * M_PI / 360.0);
    
            points->SetPoint(i, x, y, z);
        }
    
        points->Modified();
        polyData->Modified();
        mapper->Update();  // <- IMPORTANT: make sure the new geometry is picked up
    
        renderer->ResetCameraClippingRange();
        renderWindow->Render();
        renderWindow->WaitForCompletion();
    
        windowToImageFilter->Modified();
        windowToImageFilter->Update();
    
        
    
        frame++;
    }
    

    return EXIT_SUCCESS;
}