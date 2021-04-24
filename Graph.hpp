//
//  Graph.hpp
//  City_Graph
//
//  Created by 想要快乐却又不想长胖的🐑 on 2021/4/22.
//

#ifndef Graph_hpp
#define Graph_hpp
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#define Cities_Number 199
#define ERROR -1
#define Infinite 999
#define InfiniteMoney 20000
#include <fstream>
#include <iostream>
#include "Circular_Queue.hpp"
using namespace std;
struct City_node
{
    string nation;
    string city;
    float longitude; //经度
    float latitude;//纬度
};
struct routes_node
{
    string begin;
    string destination;
    string method;
    float time_cost = Infinite;//这是为了后面的floyd做准备
    float money_cost = InfiniteMoney;//这是为了后面的floyd做准备
    int mark = 0;//为之后的遍历做准备
    
};
class City_Graph  //采用邻接矩阵，floyd最短路径方法
{
public:
    //构造函数+变量
    City_Graph()
    {
        
    }
    vector<City_node> City_location=vector<City_node>(Cities_Number);
    routes_node routes[199][199];
    
    float floyd_time[199][199];
    int path_time[199][199]; //用于最短时间
    
    float floyd_money[199][199];
    int path_money[199][199];//用于最小花费
    
    
    
    
    //函数
    int locate_the_city_index(string name)
    {
        int index = 0;
        for (; index <199; index+=1) {
            if (name == this->City_location[index].city)
            {
                return index;
            }
        }
        return ERROR;
    }
    int Read_and_create_Routes_Graph()
    {
        ifstream _infile_route;
        _infile_route.open("/Users/huang/Xcode/OOC/City_Graph/alg-2021/routes.csv",ios::in);
        initial_for_floyd();
        for (int i =0; i<1975; i++)
        {
            char ch = 0;
            _infile_route.read(&ch, sizeof(char));
            //出发地
            string begin_city;
            while (ch!=',')
            {
                begin_city+=ch;
                _infile_route.read(&ch, sizeof(char));
            }
            
            int index_begin = locate_the_city_index(begin_city);
            
            _infile_route.read(&ch, sizeof(char)); //跳过 ','
            //目的地
            string destination;
            while (ch!=',')
            {
                destination+=ch;
                _infile_route.read(&ch, sizeof(char));
            }
            int index_des = locate_the_city_index(destination);
            
            _infile_route.read(&ch, sizeof(char)); //跳过 ','
            //交通方式
            string method;
            while (ch!=',')
            {
                method+=ch;
                _infile_route.read(&ch, sizeof(char));
            }
            routes[index_begin][index_des].method = method;
            routes[index_begin][index_des].begin = begin_city;
            routes[index_begin][index_des].destination = destination;
            _infile_route.read(&ch, sizeof(char)); //跳过 ','
            //时间
            string time;
            while (ch!=',')
            {
                time+=ch;
                _infile_route.read(&ch, sizeof(char));
            }
            stringstream times(time);
            float time_C_now = Infinite;
            times>>time_C_now;
            if (time_C_now<routes[index_begin][index_des].time_cost)
            {
                routes[index_begin][index_des].time_cost = time_C_now;
                floyd_time[index_begin][index_des] = routes[index_begin][index_des].time_cost;//为后来的floyd做准备
            }
            //花费
            _infile_route.read(&ch, sizeof(char)); //跳过 ','
            string money;
            while (ch!=',')
            {
                money+=ch;
                _infile_route.read(&ch, sizeof(char));
            }
            stringstream sdis(money);
            float money_C_now = InfiniteMoney;
            sdis>>money_C_now;
            if (money_C_now<routes[index_begin][index_des].money_cost)
            {
                routes[index_begin][index_des].money_cost = money_C_now;
                floyd_money[index_begin][index_des] = routes[index_begin][index_des].money_cost;//为后来的floyd做准备
            }
            string restline;
            getline(_infile_route,restline);//跳过后面的备注
        }
        
        return true;
    }
    void Visit_ACT(int i)
    {
        cout<<">>"<<City_location[i].city;
    }
    void BFSTraverse ()//用广度优先遍历
    {
        cout<<endl<<endl;
        int counter = 0;  //用于检查输出总数对不对
        int Visited[Cities_Number] = {0};
        Circular_Queue Q_BFS;
        int blank_space = 0;
        for (int i = 0; i<Cities_Number;i++)
        {
            if(0 == Visited[i])
            {
                blank_space = 1;
                cout<<endl;
                cout<<"一个连通分量：  "<<endl;
                Visited[i] = 1;
                Visit_ACT(i); counter +=1;
                Q_BFS.EnQueue(i);
                while (Q_BFS.QueueEmpty()!=0)
                {
                    int Search_core =-1;
                    Q_BFS.DeQueue(Search_core);
                    for (int j = 0; j<Cities_Number; j++)
                    {
                        if (routes[Search_core][j].time_cost!=Infinite && Visited[j]== 0) {
                            Visited[j]=1;
                            Visit_ACT(j); counter +=1;
                            Q_BFS.EnQueue(j);
                        }
                    }
                }
            }
            if (blank_space != 0)
            {
                cout<<endl;
                blank_space = 0;
            }
            
        }
        cout<<endl<<endl<<"输出城市总数： "<<counter<<endl;
    }
    void initial_for_floyd()//初始化4个辅助数组 time 和 money 各两个
    {
        for (int i =0; i<Cities_Number; i++)
        {
            for (int j = 0; j<Cities_Number; j++)
            {
                path_time[i][j] = -1;
                path_money[i][j] = -1;
                if (i==j) {
                    floyd_time[i][j] = 0;
                    floyd_money[i][j] = 0;
                    continue;
                }
                floyd_time[i][j] = Infinite;
                floyd_money[i][j] = InfiniteMoney;
                
            }
        }
    }
    void Floyd_time()//弗洛伊德最短路径----时间
    {
        for (int k = 0;k < Cities_Number ;k++ )
        {
            for (int i = 0; i<Cities_Number; i++)
            {
                for (int j = 0; j<Cities_Number; j++)
                {
                    if (floyd_time[i][j]>routes[i][k].time_cost+routes[k][j].time_cost)
                    {
                        floyd_time[i][j] = routes[i][k].time_cost+routes[k][j].time_cost;
                        path_time[i][j] = k;
                    }
                }
            }
        }
    }
    void Floyd_money()//弗洛伊德最短路径----花费
    {
        for (int k = 0;k < Cities_Number ;k++ )
        {
            for (int i = 0; i<Cities_Number; i++)
            {
                for (int j = 0; j<Cities_Number; j++)
                {
                    if (floyd_money[i][j] > routes[i][k].money_cost+routes[k][j].money_cost)
                    {
                        floyd_money[i][j] = routes[i][k].money_cost+routes[k][j].money_cost;
                        path_money[i][j] = k;
                    }
                }
            }
        }
    }
    void the_shortest_money_find(int city1_index,int city2_index,vector<vector<int>>&counter)//寻找出floyd图中的最短路径
    {
        vector<int> one_node;
        if (path_money[city1_index][city2_index] == -1) //用递归的办法求出所有的直达路径
        {
            one_node.push_back(city1_index);
            one_node.push_back(city2_index);
            counter.push_back(one_node);//放到一个vector二维组里，等待打印。
        }
        else
        {
            the_shortest_money_find(city1_index,path_money[city1_index][city2_index],counter);
            the_shortest_money_find(path_money[city1_index][city2_index], city2_index,counter);
        }
        
    
    }
    void print_shortest_money(vector<vector<int>> &counter,int city1,float &sum_money)//将floyd图中的最短路径打印出来--花费
    {
        int max_size  = counter.size();
        int i;
        for (i = 0; i<max_size; i++)//定位到起始点  0 是左边的值， 1 是右边的值
        {
            if(city1 == counter[i][0])
            {
                cout<<City_location[counter[i][0]].city<<"-----[花费： "<<routes[counter[i][0]][counter[i][1]].money_cost<<"]----->"<<City_location[counter[i][1]].city<<endl;
                sum_money += routes[counter[i][0]][counter[i][1]].money_cost;
                city1 = counter[i][1];//换到下一个起始点
                i = 0;
            }
        }
        
        
    }
    void the_shortest_time_find(int city1_index,int city2_index,vector<vector<int>>&counter)//寻找出floyd图中的最短路径
    {
        vector<int> one_node;
        if (path_time[city1_index][city2_index] == -1) //用递归的办法求出所有的直达路径
        {
            one_node.push_back(city1_index);
            one_node.push_back(city2_index);
            counter.push_back(one_node);//放到一个vector二维组里，等待打印。
        }
        else
        {
            the_shortest_time_find(city1_index,path_time[city1_index][city2_index],counter);//递归找到中间中转点
            the_shortest_time_find(path_time[city1_index][city2_index], city2_index,counter);
        }
        
    
    }
    void print_shortest_time(vector<vector<int>> &counter,int city1,float & sum_time)//将floyd图中的最短路径打印出来--时间
    {
        int max_size  = counter.size();
        int i;
        for (i = 0; i<max_size; i++)//定位到起始点  0 是左边的值， 1 是右边的值
        {
            if(city1 == counter[i][0])
            {
                cout<<City_location[counter[i][0]].city<<"-----[时间："<<routes[counter[i][0]][counter[i][1]].time_cost<<"h]----->"<<City_location[counter[i][1]].city<<endl;
                sum_time+=routes[counter[i][0]][counter[i][1]].time_cost;
                city1 = counter[i][1];//换到下一个起始点
                i = 0;
            }
        }
        
        
    }
    void the_shortest_money(string city1,string city2)
    {
        int city1_index = locate_the_city_index(city1);
        int city2_index = locate_the_city_index(city2);
        cout<<"起点： "<<city1<<'\t'<<"终点： "<<city2<<endl;
        if (floyd_money[city1_index][city2_index]==InfiniteMoney)
        {
            cout<<"这两个城市无路线"<<endl;
            return;
        }
        cout<<"路径： "<<endl;
        vector<vector<int>> counter_money;
        float sum_money = 0;
        the_shortest_money_find(city1_index, city2_index,counter_money);
        print_shortest_money(counter_money,city1_index,sum_money);
        cout<<"最小花费：  "<<sum_money<<endl;
    }
    
    
    
    void the_shortest_time(string city1,string city2)
    {
        int city1_index = locate_the_city_index(city1);
        int city2_index = locate_the_city_index(city2);
        cout<<"起点： "<<city1<<'\t'<<"终点： "<<city2<<endl;
        if (floyd_time[city1_index][city2_index]==Infinite)
        {
            cout<<"这两个城市无路线"<<endl;
            return;
        }
        cout<<"路径： "<<endl;
        vector<vector<int>> counter;
        float sum_time = 0;
        the_shortest_time_find(city1_index, city2_index,counter);
        print_shortest_time(counter,city1_index,sum_time);
        cout<<"最短时间：  "<<sum_time<<"h"<<endl;
    }
    
    void Client()
    {
        int continue_toll = 1;
        while (continue_toll)
        {
            int time_or_money = 0;
            cout<<"TIP：如果如果一次回车没有继续请再回车一次。"<<endl;
            cout<<"您要查询最短时间请输入：1  ;   查询最小花费请输入： 2    ,等待您的输入：  ";
            cin>>time_or_money;
            if (time_or_money !=1&&time_or_money!=2) {
                cout<<"模式选择输入错误，请重新输入"<<endl;
                cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
                continue;
            }
            cout<<endl<<endl;
            string city1,city2;
            cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
            cout<<"起始点？：  ";
            std::getline(std::cin, city1);
            cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
            cout<<"终点？：  ";
            std::getline(std::cin, city2);//这里遇到一个问题：cin没能把我输入的括号一起读进去，但是世界上有的地名是包含了括号,我换成scanf试试/不行，scanf不行，我再想想/用getline！
            //我觉得还要做一个判断，确定客户输入的城市是我们数据库里有的城市。
            int city1_index = locate_the_city_index(city1);
            int city2_index = locate_the_city_index(city2);
            if (city1_index==ERROR || city2_index == ERROR) {
                cout<<"数据库中没有您输入的城市,请重新输入"<<endl;
                cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
                continue;
            }
            switch (time_or_money) {
                case 1:
                {
//                    cout<<endl<<endl;
//                    string city1,city2;
//                    cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
//                    cout<<"起始点？：  ";
//                    std::getline(std::cin, city1);
//                    cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
//                    cout<<"终点？：  ";
//                    std::getline(std::cin, city2);  //这里遇到一个问题：cin没能把我输入的括号一起读进去，但是世界上有的地名是包含了括号,我换成scanf试试/不行，scanf不行，我再想想/用getline！
                    the_shortest_time(city1, city2);
                    cout<<"继续？ 1:继续 ， 0:结束";
                    cin>>continue_toll;
                    cin.ignore(1024,'\n');//清理缓冲区
                    cout<<endl;
                }
                    break;
                    
                case 2:
                {
//                    cout<<endl<<endl;
//                    string city1,city2;
//                    cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
//                    cout<<"起始点？：  ";
//                    std::getline(std::cin, city1);
//                    cin.ignore(1024,'\n');cout<<endl;//清理缓冲区
//                    cout<<"终点？：  ";
//                    std::getline(std::cin, city2);  //这里遇到一个问题：cin没能把我输入的括号一起读进去，但是世界上有的地名是包含了括号,我换成scanf试试/不行，scanf不行，我再想想/用getline！
                    the_shortest_money(city1, city2);
                    cout<<"继续？ 1:继续 ， 0:结束";
                    cin>>continue_toll;
                    cin.ignore(1024,'\n');//清理缓冲区
                    cout<<endl;
                    
                }
                    break;
                default:
                    break;
            }
        }
    }
                               
                            
};


#endif /* Graph_hpp */
