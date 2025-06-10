#pragma once


#include <QMainWindow>
#include <memory>
#include "strategy_sine_wave.hxx"
#include "animator.hxx"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent =0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Animator> animator;

private slots:
    // Welcome page buttons
    void on_accueil_background_button_clicked();
    void on_accueil_math_button_clicked();


    // Background page buttons
    void on_menu_button_background_clicked();




    // Math page buttons
    void on_menu_button_math_clicked();
    
};

