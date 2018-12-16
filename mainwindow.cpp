#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置阴影
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(20);
    ui->frame->setGraphicsEffect(effect);
    QGraphicsDropShadowEffect *effect1 = new QGraphicsDropShadowEffect;
    effect1->setOffset(0,0);
    effect1->setColor(QColor(0,0,0,100));
    effect1->setBlurRadius(20);
    ui->pushButton_start->setGraphicsEffect(effect1);
    QGraphicsDropShadowEffect *effect2 = new QGraphicsDropShadowEffect;
    effect2->setOffset(0,0);
    effect2->setColor(QColor(0,0,0,100));
    effect2->setBlurRadius(20);
    ui->pushButton_help->setGraphicsEffect(effect2);
    QGraphicsDropShadowEffect *effect3 = new QGraphicsDropShadowEffect;
    effect3->setOffset(0,0);
    effect3->setColor(QColor(0,0,0,100));
    effect3->setBlurRadius(20);
    ui->pushButton_close->setGraphicsEffect(effect3);
    QGraphicsDropShadowEffect *effect4 = new QGraphicsDropShadowEffect;
    effect4->setOffset(0,0);
    effect4->setColor(QColor(0,0,0,100));
    effect4->setBlurRadius(20);
    ui->pushButton_min->setGraphicsEffect(effect4);
    QGraphicsDropShadowEffect *effect5 = new QGraphicsDropShadowEffect;
    effect5->setOffset(0,0);
    effect5->setColor(QColor(0,0,0,100));
    effect5->setBlurRadius(20);
    ui->label_maintitle->setGraphicsEffect(effect5);

    //建立
    set = new Setting(nullptr);
    connect(set,SIGNAL(sendCodec(const char*, const char*)),this,SLOT(updateCodec(const char*, const char*))); //修改编码
    opframe = new opinionFrame();
    opframe->hide();
    compressFrame = new compress();
    compressFrame->hide();
    uncompressFrame = new uncompress();
    uncompressFrame->hide();

    connect(ui->pushButton_start,SIGNAL(toggled()),this,SLOT(on_pushButton_start_clicked()));
    connect(ui->pushButton_help,SIGNAL(toggled()),this,SLOT(on_pushButton_help_clicked()));
//    connect(ui->action_input,SIGNAL(toggled()),this,SLOT(on_action_input_triggered())); //菜单导入文件
    connect(ui->pushButton_min,SIGNAL(toggled()),this,SLOT(on_pushButton_min_clicked()));
    connect(this,SIGNAL(fileOpenSignal(QString,QString)),compressFrame,SLOT(updateFrame(QString,QString)));//将读取的文件同步至compressFrame
    //待优化，显示界面时才连接，关闭时断开连接。//与frame有关的信号槽为提升性能应该在创建时链接，在关闭时disconnect
    connect(opframe,SIGNAL(sendChoice(int)),this,SLOT(getChoice(int)));
    connect(opframe,SIGNAL(sendClose(int)),this,SLOT(getCloseSignal(int)));
    connect(uncompressFrame,SIGNAL(sendClose(int)),this,SLOT(getCloseSignal(int)));
    connect(compressFrame,SIGNAL(sendClose(int)),this,SLOT(getCloseSignal(int)));





}

MainWindow::~MainWindow()
{
    delete ui;
}

// 之后三个method实现全局拖拽
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void MainWindow::getChoice(int t){ //应该改为创键 新的页面 之后优化
    switch (t) {
    case 1:
        //压缩页面打开
        this->hide();
        this->opframe->hide();
        compressFrame->show();
        break;
    case 2:
        //解压页面打开;
        this->hide();
        this->opframe->hide();
        uncompressFrame->show();
        break;
    default:
        break;
    }
}

void MainWindow::getCloseSignal(int t){
    switch (t) {
    case 0:
        this->opframe->hide();
        this->show();
        break;
    case 1:
        this->show();
        compressFrame->hide();
        break;
    case 2:
        this->show();
        uncompressFrame->hide();

        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    this->hide();
    opframe->show();


}

void MainWindow::on_pushButton_close_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_help_clicked()
{
    QMessageBox::information(this,"使用帮助","压缩:点击开始--->压缩--->导入文件--->压缩并保存\n解压:点击开始--->解压--->导入Json文件--->"
                                         "导入huf文件--->解压并预览--->输出到文件\n其他：如果打开文件预览乱码说明编码有问题，点设置图标--->导入文件编码--->GBK.",QMessageBox::Yes);
}

/*
void MainWindow::on_actionclose_triggered()
{
    this->close();
}

void MainWindow::on_action_input_triggered() //导入文件并进行下一步操作
{
       QString filepath = QFileDialog::getOpenFileName(this,"打开文件",defaultPath.first(),tr("文本文件(*.txt);;哈夫曼二进制文件(*.huf);;All Files(*.*)"));
       qDebug()<<filepath;
       QString filename = filepath.split("/").last();
       QFile file(filepath);
       if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
           QMessageBox::critical(this,"打开文件错误","无法打开以只读和文本形式打开你的文件，请检查！");
       }else{
           //可以打开、直接切换到压缩文件页面并显示预览
           this->hide();
           this->opframe->hide();
           compressFrame->show();
           QTextStream txt(&file);
           QString  text;
           text = txt.readAll();
           file.close();
           emit fileOpenSignal(filename,text);
       }



}
*/

void MainWindow::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void MainWindow::on_pushButton_setting_clicked()
{

    set->show();
}

void MainWindow::updateCodec(const char * input, const char *output)
{
    compressFrame->codec.clear();
    compressFrame->codec.append(input);
    qDebug()<<compressFrame->codec.toStdString().c_str();
    uncompressFrame->codec.clear();
    uncompressFrame->codec.append(output);
    qDebug()<<uncompressFrame->codec.toStdString().c_str();
}
