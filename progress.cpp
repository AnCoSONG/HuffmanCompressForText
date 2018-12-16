#include "progress.h"
#include "ui_progress.h"

Progress::Progress(QWidget *parent,int type) :
    QWidget(parent),
    openType(type),
    ui(new Ui::Progress)

{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(20);
    ui->frame->setGraphicsEffect(effect);

    ui->pushButton_ok->setEnabled(false);
    connect(ui->pushButton_ok,SIGNAL(toggled()),this,SLOT(on_pushButton_ok_clicked()));

}

Progress::~Progress()
{
    delete ui;
}

void Progress::on_pushButton_ok_clicked()
{
    this->close();
}

void Progress::on_progressBar_valueChanged(int value)
{
    if(value==100){
        ui->pushButton_ok->setEnabled(true);
    }
    if(openType==0){
        if(value<5){
            ui->label_status->setText("Open file");
        }else if(value <25){
            ui->label_status->setText("Create Huffman Tree");
        }else if (value < 50){
            ui->label_status->setText("Coding");
        }else if (value < 75){
            ui->label_status->setText("Save Json File");
        }else if(value<100){
            ui->label_status->setText("Cal ratio...");
        }else {
            ui->label_status->setText("Suc! "+QString("压缩率: ")+QString::number(ratio*100,'f',2)+QString("%"));
        }
    }else if (openType == 1){

    }

}

void Progress::updatePosition(int value)
{
    ui->progressBar->setValue(value);
}

void Progress::setRatio(double ratio)
{
    this->ratio = ratio;
}


// 之后三个method实现全局拖拽
void Progress::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void Progress::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void Progress::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}
