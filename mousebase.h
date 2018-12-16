#ifndef MOUSEBASE_H
#define MOUSEBASE_H

#include <QObject>
#include <QWidget>
#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

class mouseBase : public QObject
{
    Q_OBJECT
public:
    explicit mouseBase(QObject *parent = nullptr);

    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);


signals:

public slots:
};

#endif // MOUSEBASE_H
