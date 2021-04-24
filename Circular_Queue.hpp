//
//  Circular_Queue.hpp
//  Circular_Queue
//
//  Created by 想要快乐却又不想长胖的🐑 on 2021/4/14.
//

#ifndef Circular_Queue_hpp
#define Circular_Queue_hpp

#include <stdio.h>
//这里判断是否队列满的方法是少用一个存储区，以rear的下一个位置是front作为队满的标志
class Circular_Queue
{
public:
    int* base;
    int front;//头索引，指向队列第一个数据元素
    int rear;//尾索引，指向下一个可以插入的位置
    int Max_size;
    int Add_Size;
    
public:
    Circular_Queue();
    int InitQueue();//初始化队列
    int DestroyQueue();//释放队列内存
    int ClearQueue();//清空队列
    int QueueEmpty();//判断队列是否为空，空返回ERROR 不空返回true
    int QueueLength();//求队列长度
    int GetHead(int & result);//查询队首元素
    int EnQueue(int & target);//元素入队列尾
    int DeQueue(int & result);//弹出队首元素
    int QueueTraverse();//遍历队列
};


#endif /* Circular_Queue_hpp */
