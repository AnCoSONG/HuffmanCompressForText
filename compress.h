#ifndef COMPRESS_H
#define COMPRESS_H

#include <QWidget>
#include <QGraphicsEffect>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QIODevice>

#include <QTextCodec>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>


#include "util/huffmantree.h"
#include "progress.h"
namespace Ui {
class compress;
}

class compress : public QWidget
{
    Q_OBJECT

public:
    explicit compress(QWidget *parent = nullptr);
    ~compress();
    QString originPath; //源文件路径
    QString codec = "gbk"; //打开文件的默认编码
    QString line; //存储文件名
    QString text; //存储文本内容
    HuffmanTree* huff; //哈夫曼树工具类

    Progress* pro; //进度条类

    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);






private slots:
    void on_pushButton_close_clicked();

    void updateFrame(QString,QString);

    void on_pushButton_input_clicked();

    void on_pushButton_compress_clicked();

private:
    Ui::compress *ui;
signals:
    void sendClose(int);
    void sendProgressValue(int value);
    void sendRatio(double ratio);

};

#endif // COMPRESS_H
