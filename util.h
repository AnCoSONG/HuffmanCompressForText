#ifndef UTIL_H
#define UTIL_H

#include<QFile>
#include<QString>
#include <QTextStream>
#include<QIODevice>
#include <QDebug>

//QString readTXT(QFile file){//这里没法关闭file，因此弃用
//    QTextStream txt(&file);
//    QString  text;
//    while (!txt.atEnd()) {
//        text += txt.readLine();
//        qDebug()<<text;
//    }

//    return text;
//}

#endif // UTIL_H
