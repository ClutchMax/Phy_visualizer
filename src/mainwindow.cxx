#include "../gui/ui_mainwindow.h"
#include "../include/mainwindow.hxx"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget_main->setCurrentWidget(ui->accueil);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_accueil_background_button_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->background_gen_page);
}

void MainWindow::on_accueil_math_button_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->math_page);
}



void MainWindow::on_menu_button_background_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->accueil);
}




void MainWindow::on_menu_button_math_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->accueil);
}


// void MainWindow::init_math_render()
// {
//     QVTKOpenGLNativeWidget* vtkWidget = ui->vtkWidget_math;
//     auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
//     vtkWidget->setRenderWindow(renderWindow);


//     double amplSliderVal = ui->amplSlider->value();

//     auto strategy = std::make_unique<SineWaveStrategy>(8, amplSliderVal);
//     auto animator = std::make_unique<Animator>(renderWindow, std::move(strategy));
//     animator->start();



//     QObject::connect(ui->amplSlider, &QSlider::valueChanged, animator.get(), [animator = animator.get()](int value) {
//         animator->setAmplitude(static_cast<double>(value));
//     });

// }


