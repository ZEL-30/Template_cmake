#include "main_window.h"


CWidget::CWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_CWidget)
{
    ui->setupUi(this);

}

CWidget::~CWidget()
{
    delete ui; 
}