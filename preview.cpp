#include "preview.h"
#include "ui_preview.h"

Preview::Preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    //设置阴影
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(effect);


    //链接
    connect(ui->pushButton_close,SIGNAL(toggled()),this,SLOT(on_pushButton_close_clicked()));
}

Preview::~Preview()
{
    delete ui;
}

void Preview::on_pushButton_close_clicked()
{
    this->close();
}
