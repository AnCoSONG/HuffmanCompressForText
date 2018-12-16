//
// Created by songj on 2018/12/2.
//

#ifndef ANCOUTILIZE_ANCOBINARYTREENODE_H
#define ANCOUTILIZE_ANCOBINARYTREENODE_H

template <typename E>
class AnCoBinaryTreeNode {
private:
    E value;
    AnCoBinaryTreeNode<E>* left;
    AnCoBinaryTreeNode<E>* right;
    AnCoBinaryTreeNode<E>* parent;
public:
    AnCoBinaryTreeNode(E value, AnCoBinaryTreeNode<E> *left= nullptr,
            AnCoBinaryTreeNode<E> *right= nullptr,AnCoBinaryTreeNode<E>* parent= nullptr) : value(value), left(left),
            right(right),parent(parent) {}
    void setLeft(AnCoBinaryTreeNode<E>* anCoBinaryTreeNode){
        anCoBinaryTreeNode->setParent(this);
        left = anCoBinaryTreeNode;
//        left = new AnCoBinaryTreeNode<E>(anCoBinaryTreeNode->value, nullptr,nullptr,this);
    }

    void setLeft(E value){
        left = new AnCoBinaryTreeNode<E>(value,nullptr,nullptr,this);
    }

    void setRight(AnCoBinaryTreeNode<E>* anCoBinaryTreeNode){
        anCoBinaryTreeNode->setParent(this);
        right = anCoBinaryTreeNode;
//        right = new AnCoBinaryTreeNode<E>(anCoBinaryTreeNode->value, nullptr,nullptr,this);
    }
    void setRight(E value){
        right = new AnCoBinaryTreeNode<E>(value, nullptr, nullptr,this);
    }
    void setParent(AnCoBinaryTreeNode<E>* parent) {
        this->parent = parent;
    }

    void setValue(E value){
        this->value = value;
    }

    bool hasLeft(){
        return left != nullptr;
    }
    bool hasRight(){
        return right != nullptr;
    }

    E getValue(){
        return value;
    }

    AnCoBinaryTreeNode<E>* getParent(){
        return parent;
    }

    AnCoBinaryTreeNode<E>* getLeft(){
        return hasLeft()?left: nullptr;
    }

    AnCoBinaryTreeNode<E>* getRight(){
        return hasRight()?right: nullptr;
    }

    bool isLeaf(){
        return !(hasRight()||hasLeft());
    }

    bool isRoot(){
        return parent!= nullptr;
    }





};


#endif //ANCOUTILIZE_ANCOBINARYTREENODE_H
