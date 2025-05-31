#include "../include/animator.hxx"
#include <vtkNamedColors.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <cmath>


Animator::Animator(vtkGenericOpenGLRenderWindow* rwin, 
                    std::unique_ptr<AnimationStrategy> strat,
                    QObject* parent)
    : QObject(parent), 
      renderWindow(rwin), 
      strategy(std::move(strat))
{
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

    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1000, 500);
    renderer->ResetCamera();
    renderer->GetActiveCamera()->SetPosition(0, -500, 1000);
    renderer->GetActiveCamera()->SetFocalPoint(0, 0, 0);
    renderer->GetActiveCamera()->SetViewUp(0, 1, 0);

    connect(&timer, &QTimer::timeout, this, &Animator::updateFrame);
}


void Animator::start() {
    timer.start(30);  // ~33 fps
}





void Animator::updateFrame(){
    strategy->updatePoints(points, frame);

    points->Modified();
    polyData->Modified();
    mapper->Update();
    renderer->ResetCameraClippingRange();
    renderWindow->Render();

    frame = (frame + 1) % 360;
}


AnimationStrategy* Animator::getStrategy() const {
    return strategy.get();
}



