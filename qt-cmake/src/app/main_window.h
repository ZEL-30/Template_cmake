#pragma once
#include "ui_main_window.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();

  private:
    Ui_MainWindow *ui;
};