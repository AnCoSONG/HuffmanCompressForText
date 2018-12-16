#include "huffmantree.h"

HuffmanTree::HuffmanTree(QString originText)
{
    codes = new QHash<QChar,QByteArray>();
    weight = new QHash<QChar,int>();
    //通过字符串获取权值
    int length = originText.length();
    oText = originText;
//    QByteArray t =  originText.toUtf8();
    QSet<QChar> eachChar;


    for(int i = 0; i < length; i ++ ){
        eachChar<<originText.at(i);
    }

    //STL Style Iterator faster than java style iterator
   QSet<QChar>::iterator it;
   for(it=eachChar.begin();it!=eachChar.end();++it){
       int count = originText.count(*it);
       qDebug()<<"char:"<<*it<<"\tcount:"<<count;
       //添加一个键值对
        this->weight->insert(*it,count);

   }

   leave = eachChar.size();
   qDebug()<<"leaves:"<<leave;

}

void HuffmanTree::setCodesIn()
{
    //将json翻译成hashtable
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonText.toUtf8(),&json_error));

    if(json_error.error != QJsonParseError::NoError){
        qDebug()<<"file open failed";
    }

    QJsonObject obj = jsonDoc.object();
    QStringList keys = obj.keys();
    //建立哈希表，将值与键相索引
    codesIn = new QHash<QString,QChar>();
    for(int i = 0; i < keys.size(); i ++ ){
        QJsonValue valueTemp = obj.value(keys.at(i));
        qDebug()<<keys.at(i).at(0)<<valueTemp.toString().toUtf8();
        codesIn->insert(valueTemp.toString(),keys.at(i).at(0));
    }
}

QString HuffmanTree::reEncode()
{
    QString result;
    QString temp;
    for(int i = 0; i < hufData.size(); i ++ ){
        qDebug()<<"hufdata:"<<i<<hufData.at(i);
        if(hufData.at(i)){
            temp.append('1');
        }else{
            temp.append('0');
        }

        if(codesIn->contains(temp)){
            result.append(codesIn->value(temp)); //将那个字符添加到结果字符串中
            qDebug()<<"result: "<<result;
            temp.clear();//清空temp
            qDebug()<<"temp: "<<temp;
        }
    }
    reEncodeResult = result;
    return result;
}

HuffmanTree::HuffmanTree(QString jsonPath, QString hufPath)
{

    QFile jsonF(jsonPath);
    if(!jsonF.open(QIODevice::ReadOnly)){
        qDebug()<<"decompress open json error";
        QMessageBox::critical(nullptr,"错误:json open error","解压时无法打开编码表");
    }
    jsonText = jsonF.readAll();
    qDebug()<<"jsonText"<<jsonText;
    jsonF.close();
    QFile hufF(hufPath);
    if(!hufF.open(QIODevice::ReadOnly)){
        qDebug()<<"huf file open error";
    }
    QDataStream hufD(&hufF);
    hufD.setVersion(QDataStream::Qt_5_11);
    hufD>>hufData;
    qDebug()<<hufData;
    hufF.close();

}

/*
//解压方法直接写到了解压对应的构造函数里，需要重新分步封装一下
//HuffmanTree::HuffmanTree(QByteArray json, QBitArray huf)
//{
//    //将json翻译成hashtable
//    QJsonParseError json_error;
//    QJsonDocument jsonDoc(QJsonDocument::fromJson(json,&json_error));

//    if(json_error.error != QJsonParseError::NoError){
//        qDebug()<<"file open failed";
//    }

//    QJsonObject obj = jsonDoc.object();
//    QStringList keys = obj.keys();
//    //建立哈希表，将值与键相索引
//    codesIn = new QHash<QByteArray,QChar>();
//    for(int i = 0; i < keys.size(); i ++ ){
//        QJsonValue valueTemp = obj.value(keys.at(i));
//        qDebug()<<keys.at(i).at(0)<<valueTemp.toString().toUtf8();
//        codesIn->insert(valueTemp.toString().toUtf8(),keys.at(i).at(0));
//    }


//    QString result;
//    QString temp;
//    for(int i = 0; i < huf.size(); i ++ ){
//        temp.append(huf.at(i));
//        if(codesIn->contains(temp.toUtf8())){
//            result.append(codesIn->value(temp.toUtf8())); //将那个字符添加到结果字符串中
//            qDebug()<<"result: "<<result;
//            temp.clear();//清空temp
//            qDebug()<<"temp: "<<temp;
//        }
//    }
//    //将result作为返回值发送出去以更新界面
//}
*/


AnCoBinaryTree<valuePoint<QChar, int>>* HuffmanTree::createTree()
{

    /**
      *
      * 1.每个权值创建为二叉树树根
      * 2. 根据二叉树树根值的大小排序
      * 3. 循环联合，每次联合最小的两个小树，大树在右边，小树在左边
      * 4. 当只有最后一个树根的时候则哈夫曼树建好了.
      *
      */
    QHash<QChar,int>::const_iterator it;
    QList<AnCoBinaryTree<valuePoint<QChar, int>>*>* treeList;
    treeList = new QList<AnCoBinaryTree<valuePoint<QChar, int>>*>();
    for(it=weight->cbegin();it!=weight->cend();++it){
        qDebug()<<"key:"<<it.key()<<"\tvalue:"<<it.value();
        //这边建树、添加到树表里
//        AnCoBinaryTree<valuePoint<QChar,int>> *t = new AnCoBinaryTree<valuePoint<QChar,int>>(valuePoint<QChar, int>(it.key(),it.value()));

        treeList->append(new AnCoBinaryTree<valuePoint<QChar,int>>(valuePoint<QChar, int>(it.key(),it.value())));

        //排序、联合最小的两个、循环

        //当树表里只有一个树的时候，完毕，建树完成


    }



    while(treeList->length()>1){

        // 先排序
//        auto sort = new QuickSort<QList<AnCoBinaryTree<valuePoint<QChar, int>>>>( treeList,treeList->length() );
//        sort->QSort(0,treeList->length()-1);

        for(int t = 0 ; t < treeList->length(); t ++ ){
            bool swap = false;

            for(int j = 0; j < treeList->length()- t - 1 ; j ++ ){
                auto a = treeList->at(j);
                auto b = treeList->at(j+1);

                if(a->getRootValue().value>b->getRootValue().value){
                    treeList->swap(j,j+1);
                    swap = true;
                }

            }
            if(!swap){ //如果这一次没有交换说明已经排序完成，跳出即可
                break;
            }


        }

        // 取出最开始的元素
        auto a = treeList->takeFirst();
        auto b = treeList->takeFirst();
        auto c = a->unionTree(b);
        treeList->push_back(c);

    }
    auto finalTree = treeList->takeFirst();
    finalTree->printTree(finalTree->getRoot());
//   qDebug()<<finalTree->getRoot()->isLeaf()<<finalTree->getRoot()->getLeft()->hasLeft(); 右节点不为空？？？不知道为什么
    this->tree = finalTree;

    return finalTree;
}


QByteArray HuffmanTree::writeTree()
{

    coding(tree->getRoot(),new QString());

    //再将codes存成json就OK了
    QJsonObject t;
    QHash<QChar,QByteArray>::const_iterator it; //这个hash说明codes写入有问题！！已解决！但是结果只显示4个不知道为什么...
    for(it = codes->constBegin();it!=codes->constEnd();++it){
        qDebug()<<"codes: key:"<<it.key()<<"value:"<<it.value();
        QJsonValue tv(QString::fromStdString(it.value().toStdString()));
        t.insert(it.key(),tv);
    }

    QJsonDocument jsonDoc(t);
    QByteArray json = jsonDoc.toJson(QJsonDocument::Indented);
    //选取保存路径
    QString jsonPath = QFileDialog::getSaveFileName(nullptr,"保存json文件",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),"json文件(*.json);;All Files(*.*)");
    QFile file(jsonPath);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"json file open error";
    }
    QTextStream jsonData(&file);
    jsonData.setCodec("utf-8");
    jsonData<<json;
    qDebug()<<json;
    file.close();

    return json;
}

/*
void HuffmanTree::getCode(AnCoBinaryTreeNode<valuePoint<QChar, int> > *root, QString *result, int dir)
{//待debug
    if(root==nullptr){
        return;
    }
    if(root->isLeaf()){
        leaveTime++;
        if(leaveTime>leave){
            qDebug()<<"time to return";
            return;
        }
        qDebug()<<"is leave";
        QByteArray t = result->toUtf8();
        qDebug()<<root->getValue().key<<"byte array:"<<t;
        codes->insert(root->getValue().key,t);//将结果插入codes编码集 这里有问题！！！
        switch (dir) {
        case 0://左
            *result = (result->left(result->length()-1)); //删除最后一个字符
            result->push_back('1');
            qDebug()<<"move to Parent and move to Right";
            getCode(root->getParent()->getRight(),result,1); //返回父节点并对右节点getCode
            break;
        case 1:
            *result = (result->left(result->length()-2));
            result->push_back('1');
            qDebug()<<"move to Parent and move to Parent and then move to Right";
            getCode(root->getParent()->getParent()->getRight(),result,1);//有点问题，如果此时右节点在树的右边，那么会导致重复编码（设想的解决方案，在左子树加一个如果编码节点已经包含则跳出）
            break;
        default:
            break;
        }
    }else{
        qDebug()<<"move to left";
        result->push_back('0');//将0添加到result中
        getCode(root->getLeft(),result,0);
    }
}
*/

void HuffmanTree::coding(AnCoBinaryTreeNode<valuePoint<QChar, int> > *root, QString *midResult)
{
    if(root == nullptr){
        return;
    }
    if(root->isLeaf()){
        qDebug()<<"is Leave";
        QByteArray t = midResult->toUtf8();
        qDebug()<<root->getValue().key<<"byte array:"<<t;
        codes->insert(root->getValue().key,t);
        return;
    }

    QString* left = new QString(midResult->append('0'));
    *midResult = midResult->left(midResult->length()-1);
    QString* right = new QString(midResult->append('1'));

    coding(root->getLeft(),left);
    coding(root->getRight(),right);
}

QByteArray HuffmanTree::showHuf()
{
    QBitArray bitResult;
    QByteArray byteResult;

    for(int i = 0 ; i < oText.length();i++){
        QChar temp = oText.at(i);
        QByteArray t = codes->value(temp);
        byteResult.append(t);
    }
    int bit = 0; //位置
    int byteSize = byteResult.size(); //位数
    bitResult.resize(byteSize);
    for(int i = 0; i < oText.length(); i ++ ){
        QByteArray temp = codes->value(oText.at(i));
        for(int t = 0; t < temp.size(); t ++ ){
            bitResult.setBit(bit++,temp.at(t)=='1');
        }
    }


   QString savePaths = QFileDialog::getSaveFileName(nullptr,"保存",QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first(),"哈夫曼二进制文件(*.huf);;All Files(*.*)");
   savepath = savePaths;
    QFile hufSave(savePaths);
    hufSave.open(QIODevice::WriteOnly);
    QDataStream out(&hufSave);

    out.setVersion(QDataStream::Qt_5_11);
    out<<bitResult;
    this->result = byteResult;
    hufSave.close();
    //显示预览情况
//    //将bitarray读入预览一下
//    QFile hufOpen(savePaths);
//    hufOpen.open(QIODevice::ReadOnly);

//    QDataStream in(&hufOpen);
//    in.setVersion(QDataStream::Qt_5_11);
//    QBitArray te;
//    in >> te;
//    hufOpen.close();

//    qDebug()<<"bit :"<<te;
    qDebug()<<this->result;

    return byteResult;

}

double HuffmanTree::calRatio(QString originPath, QString hufPath)
{
    //将源文件大小与新文件大小进行除法得到压缩率
    //使用QFileInfo获取大小并进行比较
    QFileInfo origin(originPath);
    QFileInfo huf(hufPath);
    double o = origin.size();
    double h = huf.size();
    return o/h;
}


