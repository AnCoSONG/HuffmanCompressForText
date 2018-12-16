#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include<QJsonParseError>
#include <QJsonDocument>
#include <QHash>
#include <QChar>
#include <QSet>
#include <QSetIterator>
#include <QHashIterator>
#include <QString>
#include <QDebug>
#include <QStack>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QBitArray>
#include <QFileInfo>
#include <QString>
#include <QMessageBox>
#include "valuepoint.h"
#include "AnCoBinaryTree.h"

/**
 * @brief The HuffmanTree class 包含建树、编码的哈夫曼类
 */
class HuffmanTree
{

public:
   //解压
    QString jsonText; //json文本
    QBitArray hufData; //huf二进制数据
    QString reEncodeResult; //解码后的文本文件

    void setCodesIn();

    QString reEncode();

    /**
     * @brief codesIn 读入文件后存储键值的哈希表
     */
    QHash<QString,QChar>* codesIn;

    /**
     * @brief HuffmanTree 哈夫曼树解压构造函数,根据json和huf文件得到原文本
     * @param json json文件字节数组
     * @param huffmanText 二进制编码后的文件
     */
    HuffmanTree(QString jsonPath,QString hufPath);


    /**
     * @brief HuffmanTree 压缩构造函数， 根据原始文本得到权值键值对
     * @param originText 原始文本
     */
    HuffmanTree(QString originText);

    /**
     * @brief oText 原始文本
     */
    QString oText;

    /**
     * @brief result 结果文本
     */
    QString result;
    /**
     * @brief weight 权重哈希表
     */
    QHash<QChar, int>*  weight;

    /**
     * @brief codes 编码表 用于输出json文件
     */
    QHash<QChar,QByteArray>* codes;



    /**
     * @brief tree 建好之后的哈夫曼树
     */
    AnCoBinaryTree<valuePoint<QChar,int>>* tree;



    /**
     * @brief createTree 利用权值哈希表，建立哈夫曼树
     */
    AnCoBinaryTree<valuePoint<QChar, int>>* createTree();

    /**
     * @brief writeTree 输出哈夫曼树的哈夫曼编码,输出json文件并返还json的qbytearray
     */
    QByteArray writeTree(); //这里有问题!!!
/*
//    //！！！NOT WORK FOR DEEP TREE ，NEED TO CORRECT ！！
//    //Theoryly work!!!
//    //从root节点开始，先判断是否为空，为空则返回
//    //再判断是否为叶子 为叶子节点的话就讲result的值赋值给一个QByteArray并将这个QByteArray添加到hashtable中
//    //之后将判断dir是0还是1：0  就返回父节点，result删除最后一个字符，将1添加到result中，并对右节点getCode； 1 就返回父节点并返回父节点，pop_back 2 个字符再将 "1" push_back
//    //再对右结点getCode
//    //如果不是叶子节点：对左节点getCode 并将"0" 添加到result中
//    //DEPRECATED!!!
//    void getCode(AnCoBinaryTreeNode<valuePoint<QChar,int>>* root,QString* result, int dir); // dir 0 left, 1 right
*/
    /**
     * @brief coding 前序递归遍历获得编码，添加到codes哈希表中
     * @param root 起点
     * @param midResult 中间结果，用来传递结果的字符串...在函数中还会生成很多这样的字符串，在程序结束之后会被释放.
     */
    void coding(AnCoBinaryTreeNode<valuePoint<QChar,int>>* root,QString* midResult);

    /**
     * @brief leave 叶子节点数目
     */
    int leave = 0;
    /**
     * @brief showHuf 显示哈夫曼编码后的文本预览(弹出预览窗口)，并输出.huf文件
     * @return 哈夫曼编码之后的字节数组
     */
    QByteArray showHuf();

    /**
     * @brief calRatio 获取压缩率
     * @param originPath 源文件路径
     * @param hufPath 哈夫曼文件路径
     * @return 返回压缩率
     */
    double calRatio(QString originPath,QString hufPath);

    QString savepath;





};

#endif // HUFFMANTREE_H
