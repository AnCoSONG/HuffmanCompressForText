#include "uncompress.h"
#include "ui_uncompress.h"

uncompress::uncompress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uncompress)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(20);
    ui->frame->setGraphicsEffect(effect);
    connect(ui->pushButton_close,SIGNAL(toggled()),this,SLOT(on_pushButton_close_clicked()));
    connect(ui->pushButton_input1,SIGNAL(toggled()),this,SLOT(on_pushButton_input1_clicked()));
    connect(ui->pushButton_input2,SIGNAL(toggled()),this,SLOT(on_pushButton_input2_clicked()));
    connect(ui->pushButton_uncompress,SIGNAL(toggled()),this,SLOT(on_pushButton_uncompress_clicked()));
    connect(ui->pushButton_save,SIGNAL(toggled()),this,SLOT(on_pushButton_save_clicked()));
}


uncompress::~uncompress()
{
    delete ui;
}



void uncompress::on_pushButton_close_clicked()
{
    ui->lineEdit_json->clear();
    ui->lineEdit__huf->clear();
    ui->textEdit->clear();
    emit sendClose(2);
}

void uncompress::on_pushButton_input1_clicked()
{
    //打开文件选择器获取要打开json文件地址，存储这个地址
    jsonPath = QFileDialog::getOpenFileName(this,"选取json文件",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),tr("json文件(*.json);;All Files(*.*)"));
    ui->lineEdit_json->setText(jsonPath);
    QFileInfo info(jsonPath);
    if(info.fileName().split('.').last().toLower()!="json"){
        QMessageBox::warning(this,"警告","文件格式错误\n请重新导入JSON文件！");
    }
}

void uncompress::on_pushButton_input2_clicked()
{
    //打开文件选择器获取要打开huf文件地址，存储这个地址
    hufPath = QFileDialog::getOpenFileName(this,"选取huf文件",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),tr("哈夫曼编码文件(*.huf);;All Files(*.*)"));
    ui->lineEdit__huf->setText(hufPath);
    QFileInfo info(hufPath);
    if(info.fileName().split('.').last().toLower()!="huf"){
        QMessageBox::warning(this,"警告","文件格式错误\n请重新导入HUF文件！");
    }
}

void uncompress::on_pushButton_uncompress_clicked()
{
    //将文件读进来
    huff = new HuffmanTree(jsonPath,hufPath);
    huff->setCodesIn();
    QString text = huff->reEncode();
    outText = text;
    ui->textEdit->setText(text);
    //改良解码函数，
    //将接受参数调整为文件路径
    //调用huffmanTree解压模块，进行解压
//    huff = new HuffmanTree()；
    //打开进度条，更新进度情况

    //完成后关闭进度条，更新显示预览结果，考虑制作一个预览界面，可以读去文本和huf文件并显示

}

void uncompress::on_pushButton_save_clicked()
{
    //保存到桌面的一个位置
    QString sPath = QFileDialog::getSaveFileName(this,"保存还原文件",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),tr("文本文件(*.txt);;All Files(*.*)"));
    QFile sF(sPath);
    if(!sF.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"无法打开这个文件";
    }
    QTextStream out(&sF);
    out.setCodec(codec.toStdString().c_str());
    out<<outText;

    sF.close();
    qDebug()<<"save done";
}

// 之后三个method实现全局拖拽
void uncompress::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void uncompress::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void uncompress::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}
