/*
 * 程序: demo00
 * 功能: 
 * 作者: ZEL
 */

#include "main_window.h"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWidget w;
    w.show();
    return a.exec();
}