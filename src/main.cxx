// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QSlider>
#include "../include/mainwindow.hxx"
#include "../include/animator.hxx"
#include "../include/animation_strategy.hxx"
#include "../include/strategy_sine_wave.hxx"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

int main(int argc, char *argv[]) {

    // -------------- Generate Application UI -----------------
    QApplication app(argc, argv);

    MainWindow mainWindow;
      
    


    

    mainWindow.show();
    return app.exec();
}

