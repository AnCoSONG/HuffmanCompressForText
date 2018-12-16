#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>
#include <QGraphicsEffect>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class Progress;
}

class Progress : public QWidget
{
    Q_OBJECT

public:
    explicit Progress(QWidget *parent = nullptr,int type = 0 );
    ~Progress();
    double ratio = 0.0;
    int openType = 0; // 0 is compress mode 1 is decompress mode

    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);

private slots:
    void on_pushButton_ok_clicked();

    void on_progressBar_valueChanged(int value);

    void updatePosition(int value);

    void setRatio(double ratio);




private:
    Ui::Progress *ui;
};

#endif // PROGRESS_H
