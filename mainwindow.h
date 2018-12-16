#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opinionframe.h"
#include "compress.h"
#include "uncompress.h"
#include "setting.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>
#include <QTextStream>
#include <QGraphicsEffect>
#include <QFile>
#include <QIODevice>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>


#include "util.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    opinionFrame* opframe; //存储每次创建的选项页面指针
    compress* compressFrame; //存储每次创建出来的压缩页面指针
    uncompress* uncompressFrame; //存储每次创建的解压页面指针
    Setting* set;

    QStringList defaultPath=QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);

private slots:

    void on_pushButton_start_clicked();

    void getChoice(int);

    void getCloseSignal(int);


    void on_pushButton_close_clicked();

    void on_pushButton_help_clicked();
    
//    void on_actionclose_triggered();

//    void on_action_input_triggered();

    void on_pushButton_min_clicked();

    void on_pushButton_setting_clicked();

    void updateCodec(const char*, const char*);

private:
    Ui::MainWindow *ui;
signals:
    void fileOpenSignal(QString,QString);
};

#endif // MAINWINDOW_H
