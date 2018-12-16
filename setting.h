#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QButtonGroup>
#include <QGraphicsEffect>
#include <QDebug>
#include <cstring>
#include <string>

#include <QCursor>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    std::string inputCodec = "utf-8";
    std::string outputCodec = "utf-8";

    QButtonGroup input;
    QButtonGroup output;

    const char* getInputCodec();

    const char* getOutputCodec();


    //拖动用变量
    bool bPressFlag = false;
    QPoint beginDrag;
    //拖拽用方法
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent*);


private slots:
    void on_pushButton_yes_clicked();

signals:
    void sendCodec(const char*, const char*);

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
