// sine_animator.cxx
#include "../include/geometry_2d.hxx"
#include <vtkNamedColors.h>
#include <vtkPolyLine.h>
#include <vtkCellArray.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <cmath>

SineAnimator::SineAnimator(vtkGenericOpenGLRenderWindow* rwin, QObject* parent)
    : QObject(parent), renderWindow(rwin), frame(0)
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

    connect(&timer, &QTimer::timeout, this, &SineAnimator::updateFrame);
}

void SineAnimator::start() {
    timer.start(30);  // ~33 fps
}

void SineAnimator::updateFrame() {
    for (int i = 0; i < 400; i++) {
        double x = 100 * (2 * M_PI) * static_cast<double>(i) / 400 - 100 * M_PI;
        double y = 100 * sin((i + frame) * 8 * M_PI / 360.0);
        double z = 100 * cos((i + frame) * 8 * M_PI / 360.0);
        points->SetPoint(i, x, y, z);
    }

    points->Modified();
    polyData->Modified();
    mapper->Update();
    renderer->ResetCameraClippingRange();
    renderWindow->Render();

    frame = (frame + 1) % 360;
}
