// main.cpp
#include <QApplication>
#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../include/geometry_2d.hxx"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

int main(int argc, char *argv[]) {

    // -------------- Generate Application UI -----------------
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);

    // Assuming your promoted widget in Qt Designer is named 'vtkWidget'
    QVTKOpenGLNativeWidget* vtkWidget = ui.vtkWidget;





    // -------------- Generate Render side -----------------

    // VTK Setup
    auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);

    auto animator = new SineAnimator(renderWindow);
    animator->start();




    // -------------- Manage geometry to render -----------------
    

    mainWindow.show();
    return app.exec();
}

