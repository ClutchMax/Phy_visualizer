#include "../include/strategy_sine_wave.hxx"
#include <vtkNamedColors.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <cmath>

SineWaveStrategy::SineWaveStrategy() 
    : SineWaveStrategy(500, 800, 8.0, 100.0) {}

SineWaveStrategy::SineWaveStrategy(int height, int width, double freq, double amp)
    : height(height), width(width), frequency(freq), amplitude(amp), type("sine") {
        vtkNew<vtkNamedColors> colors;

    points = vtkSmartPointer<vtkPoints>::New();
    for (int i = 0; i < 400; i++) {
        points->InsertNextPoint(0, 0, 0);
    }

    vtkNew<vtkPolyLine> polyLine;
    polyLine->GetPointIds()->SetNumberOfIds(400);
    for (unsigned int i = 0; i < 400; i++) {
        polyLine->GetPointIds()->SetId(i, i);
    }

    vtkNew<vtkCellArray> cells;
    cells->InsertNextCell(polyLine);

    polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetLines(cells);

    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);

    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("Tomato").GetData());
    
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(colors->GetColor3d("Black").GetData());
    renderer->AddActor(actor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->SetPosition(0, -500, 1000);
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);

}

SineWaveStrategy::~SineWaveStrategy() = default;

void SineWaveStrategy::updateAnim(int frame) {
    for (int i = 0; i < 400; ++i) {
        double x = 100 * (2 * M_PI) * static_cast<double>(i) / 400 - 100 * M_PI;
        double y = amplitude * sin((i + frame) * frequency * M_PI / 360.0);
        double z = amplitude * cos((i + frame) * frequency * M_PI / 360.0);
        points->SetPoint(i, x, y, z);
    }
    points->Modified();
    polyData->Modified();
    mapper->Update();
    renderer->ResetCameraClippingRange();
}





std::string SineWaveStrategy::getType(){
    return type;
}

void SineWaveStrategy::setAmplitude(double ampl){
    amplitude = ampl;
}
