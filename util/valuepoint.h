#ifndef VALUEPOINT_H
#define VALUEPOINT_H

#include<QString>
#include <iostream>
#include <string>
#include<QDebug>
using namespace std;
template<typename E, typename T >
class valuePoint
{
public:
    E key;
    T value;
    valuePoint(E key, T value){
        this->key = key;
        this->value = value;

    }

    const valuePoint operator+(const valuePoint& v1){
         return valuePoint(E(),this->value+v1.value);
    }

    const T operator< (const valuePoint& v1){
        return this->value<v1.value;
    }


   friend ostream& operator<< (ostream& output, const valuePoint& v1){
        QString value(QString::number(v1.value));
        QString key(v1.key);
        QString Char("char:");
        QString Value("Value");
        qDebug()<<Char<<key<<Value<<value;
        string o = Char.append(key).append(Value).append(value).toStdString();
        output<<o<<endl;
        return output;
    }


};

#endif // VALUEPOINT_H
