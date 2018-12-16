#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(20);
    ui->frame->setGraphicsEffect(effect);


    input.addButton(ui->input_utf8,0);
    input.addButton(ui->input_gbk,1);
    output.addButton(ui->output_utf8,0);
    output.addButton(ui->output_gbk,1);

    connect(ui->pushButton_yes,SIGNAL(toggled()),this,SLOT(on_pushButton_yes_clicked()));

}

Setting::~Setting()
{
    delete ui;
}

const char *Setting::getInputCodec()
{
    return inputCodec.c_str();
}

const char *Setting::getOutputCodec()
{
    return outputCodec.c_str();
}

void Setting::on_pushButton_yes_clicked()
{
    qDebug()<<input.checkedId();
    qDebug()<<output.checkedId();
    switch (input.checkedId()) {
    case 0:
        inputCodec = "utf-8";
        break;
    case 1:
        inputCodec = "gbk";
        break;
    default:
        qDebug()<<"error input";
        break;
    }

    switch (output.checkedId()) {
    case 0:
        outputCodec = "utf-8";
        break;
    case 1:
        outputCodec = "gbk";
        break;
    default:
        qDebug()<<"error output";
        break;
    }

    emit sendCodec(getInputCodec(),getOutputCodec());
    this->hide();


}

// 之后三个method实现全局拖拽
void Setting::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Setting::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void Setting::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}
