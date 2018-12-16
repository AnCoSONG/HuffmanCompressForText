#include "opinionframe.h"
#include "ui_opinionframe.h"

opinionFrame::opinionFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::opinionFrame)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(20);
    ui->frameshadow->setGraphicsEffect(effect);

    connect(ui->pushButton_close,SIGNAL(toggled()),this,SLOT(on_pushButton_close_clicked()));
//    ui->verticalLayoutWidget->setGraphicsEffect(effect);
//    ui->pushButton_close->setGraphicsEffect(effect);

}

opinionFrame::~opinionFrame()
{
    delete ui;
}

// 之后三个method实现全局拖拽
void opinionFrame::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void opinionFrame::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void opinionFrame::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void opinionFrame::on_pushButton_txt_clicked()
{
    emit sendChoice(1);
}


void opinionFrame::on_pushButton_close_clicked()
{
    emit sendClose(0);
}

void opinionFrame::on_pushButton_huf_clicked()
{
    emit sendChoice(2);
}

