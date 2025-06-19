#include "../gui/ui_mainwindow.h"
#include "../include/mainwindow.hxx"
#include "../include/strategy_factory.hxx"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), isMathInitialized(false), isBackgroundInizialized(false)
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
    
    if(!isMathInitialized){
        QVTKOpenGLNativeWidget* vtkWidget = ui->vtkWidget_math;
        auto renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
        vtkWidget->setRenderWindow(renderWindow);
        

        double amplSliderVal = ui->amplSlider->value();

        //auto strategy = StrategyFactory::create("sine", 800, 500, 8, amplSliderVal); 
        auto strategy = StrategyFactory::create("random_wave", 800, 800, 10, amplSliderVal, 0, 40, 200);      //std::make_unique<SineWaveStrategy>(8, amplSliderVal);
        animator = std::make_unique<Animator>(renderWindow, std::move(strategy), 360, false);
        animator->start();

        

        QObject::connect(ui->amplSlider, &QSlider::valueChanged, this, [this](int value) {
            if (auto sine = dynamic_cast<SineWaveStrategy*>(animator->getStrategy())) {
                sine->setAmplitude(static_cast<double>(value));
            }
        });

        // Connect play button
        QObject::connect(ui->button_play, &QPushButton::clicked, animator.get(), &Animator::start);

        // Connect pause button
        QObject::connect(ui->button_pause, &QPushButton::clicked, animator.get(), &Animator::pause);

        QObject::connect(animator.get(), &Animator::frameUpdated, this, [=](int frame) {
            ui->label_frameNumber->setText(QString::number(frame));
        });
        
        isMathInitialized = true;
    }
}



void MainWindow::on_menu_button_background_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->accueil);
}




void MainWindow::on_menu_button_math_clicked()
{
    ui->stackedWidget_main->setCurrentWidget(ui->accueil);
    
}




