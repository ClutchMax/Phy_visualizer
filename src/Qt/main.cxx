// main.cpp
#include <QApplication>
#include <QMainWindow>
#include "ui_mainwindow.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);

    // Assuming your promoted widget in Qt Designer is named 'vtkWidget'
    QVTKOpenGLNativeWidget* vtkWidget = ui.vtkWidget;

    // VTK Setup
    auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);

    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    // Add a simple sphere
    auto sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetRadius(1.0);

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    renderer->AddActor(actor);
    renderer->ResetCamera();

    mainWindow.show();
    return app.exec();
}
