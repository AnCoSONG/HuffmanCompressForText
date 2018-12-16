#include "compress.h"
#include "ui_compress.h"

compress::compress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::compress)
{
    ui->setupUi(this);



    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0,0);
    effect->setColor(QColor(0,0,0,100));
    effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(effect);

    connect(ui->pushButton_close,SIGNAL(toggled()),this,SLOT(on_pushButton_close_clicked()));
    connect(ui->pushButton_input,SIGNAL(toggled()),this,SLOT(on_pushButton_input_clicked()));
    connect(ui->pushButton_compress,SIGNAL(toggled()),this,SLOT(on_pushButton_compress_clicked()));
}

compress::~compress()
{
    delete ui;
}

void compress::on_pushButton_close_clicked()
{
    ui->lineEdit_input->clear();
    ui->textEdit->clear();
    emit sendClose(1);
}

void compress::updateFrame(QString line,QString text){
    if(!line.isEmpty())
        this->line = line;
        ui->lineEdit_input->setText(this->line);
    if(!text.isEmpty())
        this->text = text;
        ui->textEdit->setText(this->text);
}


void compress::on_pushButton_input_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"打开文件",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),tr("文本文件(*.txt);;哈夫曼二进制文件(*.huf);;All Files(*.*)"));
    originPath = filepath;
    qDebug()<<filepath;
    QString filename = filepath.split("/").last();
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::critical(this,"打开文件错误","无法打开以只读形式打开你的文件，请检查！");
    }else{




        QFileInfo info(file);

        QString suffix = info.fileName().split('.').last().toLower(); //准备支持其他文件，二进制文件用QData流打开，文本文件用QText流打开
        if(!(suffix=="txt")){
            QMessageBox::warning(this,"警告","非文本文件暂时不受支持\n请重新导入文件！");
        }
        QTextStream txt(&file);
        txt.setCodec(codec.toStdString().c_str());

        text = txt.readAll();
        file.close();
        updateFrame(filename,text);

    }


}

void compress::on_pushButton_compress_clicked()
{
    qDebug()<<"compress start";
    pro = new Progress(this,0);
    pro->show();
    connect(this,SIGNAL(sendProgressValue(int)),pro,SLOT(updatePosition(int)));
    connect(this,SIGNAL(sendRatio(double)),pro,SLOT(setRatio(double)));

    huff = new HuffmanTree(text);

    emit sendProgressValue(15);

    huff->createTree();

    emit sendProgressValue(40);

    huff->writeTree();
    emit sendProgressValue(80);

    huff->showHuf();
    emit sendProgressValue(99);
    emit sendRatio(huff->calRatio(originPath,huff->savepath));
    free(huff);
    emit sendProgressValue(100);
    //计算压缩率



}

// 之后三个method实现全局拖拽
void compress::mouseMoveEvent(QMouseEvent *event)
{
    if(bPressFlag)
    {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void compress::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void compress::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}


