#ifndef UNCOMPRESS_H
#define UNCOMPRESS_H

#include <QWidget>
#include <QGraphicsEffect>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardPaths>
#include <QMessageBox>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

#include "util/huffmantree.h"
namespace Ui {
class uncompress;
}

class uncompress : public QWidget
{
    Q_OBJECT

public:
    explicit uncompress(QWidget *parent = nullptr);
    ~uncompress();
    QString jsonPath; //存储json文件路径
    QString hufPath; //存储huf文件路径
    HuffmanTree* huff;// 存储哈夫曼树工具

    QString outText; //还原后的文本
    QString codec = "utf-8"; //输出编码

    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);

private:
    Ui::uncompress *ui;
signals:
    void sendClose(int);

private slots:
    void on_pushButton_close_clicked();
    void on_pushButton_input1_clicked();
    void on_pushButton_input2_clicked();
    void on_pushButton_uncompress_clicked();
    void on_pushButton_save_clicked();
};

#endif // UNCOMPRESS_H
