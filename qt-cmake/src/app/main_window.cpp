#include "main_window.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui_MainWindow) {
    ui->setupUi(this);

    // 插入图片
    QPixmap pixmap(":/images/data.png");
    ui->push_btn->setIcon(pixmap);
    ui->push_btn->setIconSize(pixmap.size());
    ui->push_btn->setFixedSize(pixmap.size());
}

MainWindow::~MainWindow() { delete ui; }