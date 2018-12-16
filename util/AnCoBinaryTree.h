//
// Created by songj on 2018/12/2.
//

#ifndef ANCOUTILIZE_ANCOBINARYTREE_H
#define ANCOUTILIZE_ANCOBINARYTREE_H

#include <iostream>
#include "AnCoBinaryTreeNode.h"

using namespace std;
template <typename  E>
class AnCoBinaryTree {

    AnCoBinaryTreeNode<E>* root;
    AnCoBinaryTreeNode<E>* current;//当前位置
    int size=0;
    int depth(AnCoBinaryTreeNode<E>*) //递归获取树的深度
    {
           return 0;
    }

    void preTraverse_count(AnCoBinaryTreeNode<E>* traverseRoot){ //前序遍历
        if(traverseRoot == nullptr )
            return;
        size+=1;
        preTraverse_count(traverseRoot->getLeft()); //left first because this is preTraverse
        preTraverse_count(traverseRoot->getRight());
    }
    void preTraverse(AnCoBinaryTreeNode<E>* traverseRoot){ //前序遍历
        if(traverseRoot == nullptr )
            return;
        //do something first
        // then travserse its child
        cout<<traverseRoot->getValue()<<endl;
        preTraverse(traverseRoot->getLeft()); //left first because this is preTraverse
        preTraverse(traverseRoot->getRight());
    }

    void inTraverse(AnCoBinaryTreeNode<E>* traverseRoot){ //中序遍历
        if(traverseRoot == nullptr )
            return;
        inTraverse(traverseRoot->getLeft());


        /*
             do something to root here
        */
        cout<<traverseRoot->getValue()<<endl;

        inTraverse(traverseRoot->getRight());

    }

    void postTraverse(AnCoBinaryTreeNode<E>* traverseRoot){ //后序遍历
        if(traverseRoot == nullptr )
            return;
        postTraverse(traverseRoot->getLeft());
        postTraverse(traverseRoot->getRight());
        //do something to root
        cout<<traverseRoot->getValue()<<endl;
    }
public:
    AnCoBinaryTree(E rootValue){
        current = root = new AnCoBinaryTreeNode<E>(rootValue);
    }

    AnCoBinaryTree(AnCoBinaryTreeNode<E> *root) : root(root) {
        current = root;
    }

    int count() //获取树的节点数目
    {
        preTraverse_count(root);
        return size;
    }


    AnCoBinaryTree<E>* insertNode(E value, int direction){//插入子节点
        switch (direction){
            case 1: //插左节点
                return insertLeftNode(value);
                break;
            case 2: //插右节点
                return insertRightNode(value);
                break;
        }


    }

    AnCoBinaryTree<E>* insertLeftNode(AnCoBinaryTreeNode<E>* node){
        if(current->hasLeft()){
            cout<<"current already has left node, so this operation will change the extant node"<<endl;
            current->getLeft()->setValue(node->getValue());
        }else{
            current->setLeft(node);
        }

        current = current->getLeft();

        return this;

    }



    AnCoBinaryTree<E>* insertLeftNode(E value){
        if(!current->hasLeft()){
            current->setLeft(value); //新建节点
        }else{
            //已有左节点，赋值
            cout<<"left already has value"<<endl;
            current->getLeft()->setValue(value);

        }
        current = current->getLeft(); //将current指针指向新创建的节点

        return this;
    }

    /**
     * 联合两颗子树
     * @param unionTarget 被联合的树
     * @return 返回联合后的新树
     */

    AnCoBinaryTree<E>* unionTree(AnCoBinaryTree<E>* unionTarget){

        auto unionResult = new AnCoBinaryTree<E>(root->getValue()+unionTarget->root->getValue());
        if(root->getValue()<unionTarget->root->getValue()){
            unionResult->insertLeftNode(root)->moveToRoot()->insertRightNode(unionTarget->root);
        }else{
            unionResult->insertRightNode(root)->moveToRoot()->insertLeftNode(unionTarget->root);
        }

        return unionResult;
    }

    AnCoBinaryTree<E>* insertRightNode(AnCoBinaryTreeNode<E>* node){
        if(current->hasRight()){
            cout<<"current already has right node, so this operation will change the extant node"<<endl;
            current->getRight()->setValue(node->getValue());
        }else{
            current->setRight(node);
        }
        current = current->getRight();

        return this;
    }

    /**
     * 在parent下右子节点插入值为value的子节点
     * @param parent 它的父节点
     * @param value 它的值
     * @return 返回本树 方便继续操作
     */
    AnCoBinaryTree<E>* insertRightNode(E value){
        if(!current->hasRight()){
            current->setRight(value);

        }else{
            //已有右节点，赋值
            cout<<"right already has value"<<endl;
            current->getRight()->setValue(value);

        }
        current = current->getRight();
        return this;
    }


    AnCoBinaryTree<E>* moveToParent(){
        current = current->getParent();
        return this;
    }

    AnCoBinaryTree<E>* moveToRoot(){
        current = root;
        return this;
    }

    AnCoBinaryTree<E>* moveToLeftChild(){
        current = current->getLeft();
        return this;
    }

    AnCoBinaryTree<E>* moveToRightChild(){
        current = current->getRight();
        return this;
    }

    void printTree(AnCoBinaryTreeNode<E>* traverseRoot){ //前序遍历打印树的节点值
        if(traverseRoot == nullptr )
            return;
        //do something first
        // then travserse its child
        cout<<traverseRoot->getValue()<<endl;
        printTree(traverseRoot->getLeft()); //left first because this is preTraverse
        printTree(traverseRoot->getRight());
    }

    /**
     * 获取根节点值
     * @return 根节点的数值
     */
    E getRootValue(){
        return root->getValue();
    }

    E getCurrentValue(){
        return current->getValue();
    }

    AnCoBinaryTreeNode<E>* getRoot(){
        return root;
    }

    AnCoBinaryTreeNode<E>* getCurrent(){
        return current;
    }

    /**
     * 删除一个节点，此方法会将该节点及其子节点完整删除并删除返回之后的树
     * @param traverseRoot 被删除节点
     * @return 当前的树
     */
    AnCoBinaryTree<E>* deleteNode(AnCoBinaryTreeNode<E>* traverseRoot){
        if(traverseRoot == nullptr )
            return this;
        deleteNode(traverseRoot->getLeft());
        deleteNode(traverseRoot->getRight());


        delete traverseRoot;
    }

};


#endif //ANCOUTILIZE_ANCOBINARYTREE_H
