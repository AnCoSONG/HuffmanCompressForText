//
// Created by songj on 2018/11/14.
//

#ifndef ANCOUTILIZE_QUICKSORT_H
#define ANCOUTILIZE_QUICKSORT_H

#include <iostream>

#include <QList>
#include <QChar>
#include "AnCoBinaryTree.h"
#include "valuepoint.h"
using namespace std;

template <class E>
class QuickSort {
    E* elem;
    int length;
public:

    QuickSort(E *elem, int length) : elem(elem), length(length) {
        cout<<"Quick sort object created!"<<endl;
    }

    void display(){
        cout<<"Array Condition:"<<endl;
        for(int i = 0; i < length; i ++ ){
            cout<<elem[i]<<"\t";
        }
        cout<<endl;
    }

    int qPartition(int left, int right){
        /*
         * quick sort theory:
         *  set a key pos,L pointer R pointer
         *  L pointer move to right until it meets the first value which is bigger than key's value, switch the value of L pointer and the value of R pointer.
         *  then , R pointer move to left until it meets the first value which is smaller than the key's value , swap the value of L pointer and R pointer.
         *  keep doing this until the L and R pointer meet, switch the value of this pos and the value of key.
         *  this time the array is separated into 2 parts. doing quick sort to the child array.
         */
        int L=left; //L pointer
        int R = right; //R pointer
        int T = R--; //将right赋值给T，T存放的是枢纽值，R应该向前挪一个不影响整体。

//        E key = elem[T];  //key value ,we set the last one as the key

        do {
            while (elem[L]<elem[T]){ //这里不检测是否超过R，因为当最大元素在最后的时候，L如果停在R处则会导致错误的交换
                ++L;
            }
            while((L<R)&&(elem[R]>=elem[T])){//在以最末元素为枢纽值时，R不允许超过L
                --R;
            }
            //当LR相等时不交换LR 只有L < R时才交换，大于时说明枢纽值为最大值，此时也不进行交换
            if(L<R){
                E temp = elem[L];
                elem[L] = elem[R];
                elem[R] = temp;
            }

        }while (L<R);
        //when L equals R, swap the value of L and key
        E temp = elem[T];
        elem[T] = elem[L];
        elem[L] = temp;
        display();
        return L; // L and R equals now.
        /*
         * return the partition result , this result can divide the whole array into 2 part, the members of the left part are all smaller than KEY,
         * the member of the right part are all bigger than the key.
         */
    }

    int qPartition2(int left, int right){
        /*
         * quick sort theory:
         *  set a key pos,L pointer R pointer
         *  L pointer move to right until it meets the first value which is bigger than key's value, switch the value of L pointer and the value of R pointer.
         *  then , R pointer move to left until it meets the first value which is smaller than the key's value , swap the value of L pointer and R pointer.
         *  keep doing this until the L and R pointer meet, switch the value of this pos and the value of key.
         *  this time the array is separated into 2 parts. doing quick sort to the child array.
         */
        int L=left; //L pointer
        int R = right; //R pointer
        int T = R--; //将right赋值给T，T存放的是枢纽值，R应该向前挪一个不影响整体。

//        E key = elem[T];  //key value ,we set the last one as the key

        do {
            while (elem[L]<elem[T]){ //这里不检测是否超过R，因为当最大元素在最后的时候，L如果停在R处则会导致错误的交换
                ++L;
            }
            while((L<R)&&(elem[R]>=elem[T])){//在以最末元素为枢纽值时，R不允许超过L
                --R;
            }
            //不进行LR交换的判断

            E temp = elem[L];
            elem[L] = elem[R];
            elem[R] = temp;


        }while (L<R);
        //在这里将R和T进行交换，为什么时R和T？因为L有可能跑到R后面，而在上面得LR交换导致错误的交换，如果将LT交换就不会纠正这种错误，而用RT交换不光可以
        //满足正常的情况，还可以纠正这种特殊情况下的错误
        E temp = elem[T];
        elem[T] = elem[R];
        elem[R] = temp;
        display();
        return L; // L and R equals now.
        /*
         * return the partition result , this result can divide the whole array into 2 part, the members of the left part are all smaller than KEY,
         * the member of the right part are all bigger than the key.
         */
    }

    /**
     *
     * @param left  左边第几个开始
     * @param right  右边第几个结束
     */
    void QSort(int left ,int right){
        if(left<right){ //when right - left 》0 that means it has 2 elements at least
            int mid = qPartition(left,right); //划分得到两部分
            QSort(left,mid-1); //对小于部分排序
            QSort(mid+1,right); //对大于部分排序
        }
    }

    /**
     * @brief 这是另一个QSort 使用qPartition2 ,qPartition2是另一种可行的划分方式
     * @param left  左边第几个开始
     * @param right  右边第几个结束
     */
    void QSort2(int left ,int right){
        if(left<right){ //when right - left 》0 that means it has 2 elements at least
            int mid = qPartition2(left,right); //划分得到两部分
            QSort(left,mid-1); //对小于部分排序
            QSort(mid+1,right); //对大于部分排序
        }
    }

    template<class QList<AnCoBinaryTree<valuePoint<QChar, int>>>>
    void QSort_Specific(int left, int right){
        if(left<right){
            int min =
        }
    }

};


#endif //ANCOUTILIZE_QUICKSORT_H
