#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "argc:"<<argc<<"argv"<<argv[0];

    MainWindow w;
    w.setWindowTitle("Huffman Coding Tool");
    w.show();

    return a.exec();
}
