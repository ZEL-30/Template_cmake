#include "main_window.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui_(new Ui_MainWindow) {
    ui->setupUi(this);

    initWindow();

    initUI();

    initSignalSlot();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::initWindow() {

    // 设置窗口标题
    setWindowTitle("Template");
}

void MainWindow::initUI() {
    // 插入图片
    QPixmap pixmap(":/image/data.png");
    ui_->push_btn->setIcon(pixmap);
    ui_->push_btn->setIconSize(pixmap.size());
    ui_->push_btn->setFixedSize(pixmap.size());
}

void MainWindow::initSignalSlot() {}