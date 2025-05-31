// main.cpp
#include <QApplication>
#include <QMainWindow>
#include <QSlider>
#include "ui_mainwindow.h"
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

    QMainWindow mainWindow;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);

    // Assuming your promoted widget in Qt Designer is named 'vtkWidget'
    QVTKOpenGLNativeWidget* vtkWidget = ui.vtkWidget;
    




    // -------------- Generate Render side -----------------

    // VTK Setup
    auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkWidget->setRenderWindow(renderWindow);


    double amplSliderVal = ui.amplSlider->value();

    auto strategyRaw = new SineWaveStrategy(8, amplSliderVal);
    auto strategy = std::unique_ptr<SineWaveStrategy>(strategyRaw);

    auto animator = new Animator(renderWindow, std::move(strategy));
    animator->start();



    QObject::connect(ui.amplSlider, &QSlider::valueChanged, [strategyRaw](int value) {
        strategyRaw->setAmplitude(static_cast<double>(value));
    });


    // -------------- Manage geometry to render -----------------
    

    mainWindow.show();
    return app.exec();
}

