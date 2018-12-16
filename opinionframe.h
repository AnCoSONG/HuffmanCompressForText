#ifndef OPINIONFRAME_H
#define OPINIONFRAME_H

#include <QWidget>
#include <QGraphicsEffect>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class opinionFrame;
}

class opinionFrame : public QWidget
{
    Q_OBJECT

public:
    explicit opinionFrame(QWidget *parent = nullptr);
    ~opinionFrame();


    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);

private slots:
    void on_pushButton_txt_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_huf_clicked();

private:
    Ui::opinionFrame *ui;
signals:
    void sendChoice(int);
    void sendClose(int);
};

#endif // OPINIONFRAME_H
