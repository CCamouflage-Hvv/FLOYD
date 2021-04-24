//
//  Circular_Queue.cpp
//  Circular_Queue
//
//  Created by 想要快乐却又不想长胖的🐑 on 2021/4/14.
//

#include "Circular_Queue.hpp"
#include <iostream>
#define ERROR 0
#define Initial_Size 200
using namespace std;
Circular_Queue::Circular_Queue()
{
    InitQueue();
}

int Circular_Queue::InitQueue()
{
    
    this->base = new int[Initial_Size];
    if (base == NULL)
    {
        return ERROR;
    }
    this->Max_size= Initial_Size;
    this->front = 0;
    this->rear = 0;
    
    return true;
}

int Circular_Queue::QueueLength()
{
    return ((rear-front+Max_size)%Max_size);
}

int Circular_Queue::EnQueue(int &target)
{
    if ((rear+1)%Max_size == front)
    {
        cout<<"ERROR: EnQueue失败，队列已满 ,失败值: "<<target<<endl;
        return ERROR;
    }//判断有没有队满
    base[rear] = target;
    rear =(rear+1)% Max_size;//注意这个 取模
    return true;
}
int Circular_Queue::DeQueue(int &result)
{
    if (front == rear) {
        return ERROR;
    }//判断队是不是空
    result = base[front];//不空则队首出队列
    front = (front+1)%Max_size;
    return true;
}
int Circular_Queue::DestroyQueue()
{
    if (base==NULL) {
        return ERROR;
        
    }
    delete[]base;
    return true;
}
int Circular_Queue::GetHead(int &result)
{
    if (front == rear) {
        return ERROR;
    }//判断队是不是空
    result = base[front];//不空则获取队首元素
    //但是不一是出队列
    return true;
}
int Circular_Queue::QueueTraverse()
{
    if (front == rear) {
        return ERROR;
    }//判断队是不是空
    int i =front;
    while(i!=rear)
    {
        cout<<base[i]<<'\t';
        i = (i+1)%Max_size;
    }
    cout<<endl;
    return true;
}
int Circular_Queue::QueueEmpty()
{
    if (front == rear) {
        return ERROR;
    }
    return true;
}
int Circular_Queue::ClearQueue()
{
    rear = front;
    return true;
}
