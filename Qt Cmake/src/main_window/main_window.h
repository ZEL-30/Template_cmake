#pragma once
#include "ui_main_window.h"
#include <QMainWindow>



class CWidget : public QMainWindow {
    Q_OBJECT
    
public:
    CWidget(QWidget* parent = nullptr);
    ~CWidget();

private:
    Ui_CWidget* ui;
};