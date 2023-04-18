#include "main_window.h"


CWidget::CWidget(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_CWidget)
{
    ui->setupUi(this);



    // 插入图片
    QPixmap pixmap(":/images/data.png");
    ui->push_btn->setIcon(pixmap);
    ui->push_btn->setIconSize(pixmap.size());
    ui->push_btn->setFixedSize(pixmap.size());



}

CWidget::~CWidget()
{
    delete ui; 
}