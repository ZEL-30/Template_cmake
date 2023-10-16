#include "main_window.h"

MainWindow::MainWindow(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui_MainWindow) {
    ui->setupUi(this);

    initWindow();

    initUI();

    initSignalSlot();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initWindow() {

    // 设置窗口标题
    setWindowTitle("Template");
}

void MainWindow::initUI() {
    // 插入图片
    QPixmap pixmap(":/image/data.png");
    ui->push_btn->setIcon(pixmap);
    ui->push_btn->setIconSize(pixmap.size());
    ui->push_btn->setFixedSize(pixmap.size());
}

void MainWindow::initSignalSlot() {}