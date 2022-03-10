/**
 * @file skip_list.h
 * @author yuanyongan
 * @brief 跳表的简单实现，对插入，删除，查找功能进行实现
 * @version 0.1
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _SIMPLE_ALLOC_
#define _SIMPLE_ALLOC_

#include <iostream>
#include <vector>



namespace SIMPLE_STL{

    template<typename T>
    struct SkipListNode{
        int key;
        T value;
        std::vector<SkipListNode*> next;

        SkipListNode(int k, T v, int level);
    };

    template<typename T>
    SkipListNode<T>::SkipListNode(int k, T v, int level): key(k), value(v){
        for (int i = 0; i < level; i++)
        {
            next.push_back(nullptr);
        }
        
    }

    template<class T>
    class SkipList
    {
    
    public:
        // 头结点
        SkipListNode<T>* head;
         // 最大层数
        int max_level;

        //整型的最小值和最大值
        const int minInt = numeric_limits<int>::min();
        const int maxInt = numeric_limits<int>::max();

        // 构造和析构函数
        SkipList(int max_level, T ini_Value);
        ~SkipList();

        // 获取随机层数
        int getRandomLevel();

        // 插入 删除 查找
        SkipListNode<T>* insert(int k, T v);
        SkipListNode<T>* find(int k);
        SkipListNode<T>* deleteNode(int k);
        
    private:
        /* data */
        // 尾结点
        SkipListNode<T>* tail;
       
    };

    /**
     * @brief 跳表的初始化构造函数，初始化的时候头尾结点分别赋值整型的最小最大值用来使链表有序
     * 
     * @tparam T 
     * @param max_level 最大层数
     * @param ini_Value 初始化头尾节点的取值，类型为T
     */
    
    template<class T> SkipList<T>::SkipList(int max_level, T ini_Value) :max_level(max_level){
        // 初始化头结点和尾结点为整型的最小值和最大值，
        head = new SkipListNode<T>(minInt, ini_Value, max_level);
        tail = new SkipListNode<T>(maxInt, ini_Value, max_level);

        // 所有层数上的头结点指向尾节点
        for (int i = 0; i < max_level; i++)
        {
            head->next = tail;
        }
        
    }

    
    template<class T> SkipList<T>::~SkipList(){
        delete head;
        delete tail;
    }

    /**
     * @brief 对新插入的节点取得随机层数，这里使用的是《C++ Primer 5th Edition》里面介绍了使用default_random_engine来获取随机数，
     * 
     * @tparam T 
     * @return int 
     */
    template<class T> int SkipList<T>::getRandomLevel(){

        // 初始层数为1
        int random_level = 1;

        // 创建随机数引擎
        static default_random_engine e(time(NULL));

        // 创建随机取值范围
        static uniform_int_distribution<int> u(0,1);

        // 如果随机值为0，就层数+1，为1就停止，一半的概率
        while (u(e) && random_level < max_level)
        {
            random_level ++;
        }
        return random_level;
    }
    
    /**
     * @brief 节点插入
     * 1、插入的时候需要先判断该节点是否存在，也就是key值是否存在，存在的话要更新
     * 2、获取新节点的随机层数
     * 3、找到位置插入，并调整指针
     * 
     * @tparam T 
     * @param k 
     * @param v 
     * @return SkipListNode<T>* 一般是返回插入后的跳表的头结点
     */
    template<class T> SkipListNode<T>* SkipList<T>::insert(int k, T v){

        // 查找是否存在key，存在的话，更新value返回头结点
        SkipListNode<T>* new_node = find(k);
        if (new_node)
        {
            new_node->value = v;
            std::cout << "Node exits, replace new value" << endl;
            return head;
        }


        // 获取随机层数
        int level_for_neew_node = getRandomLevel();

        // 找到插入点
        SkipListNode<T>* tmp = head;
        new_node = new SkipListNode<T>(k, v, level_for_neew_node);


        // 从随机层数的最高层开始，给新节点的指针赋值
        for (int i = level_for_neew_node - 1; i >= 0; --i)
        {
            // 因为每一层的节点数一般比较少，所以直接遍历就好了，层数越往下，范围越小
            while (tmp->next[i] != nullptr && tmp->next[i]->key < k)
            {
                tmp = tmp->next[i];
            }
            new_node->next[i] = tmp->next[i];
            tmp->next[i] = new_node;
        }
        
        return head;
        
    }
    
}// end of namespace SIMPLE_STL
#endif

