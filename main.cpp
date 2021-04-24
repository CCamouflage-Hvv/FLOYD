//
//  main.cpp
//  City_Graph
//
//  Created by 想要快乐却又不想长胖的🐑 on 2021/4/22.
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include <vector>
#include <sstream>
#define Cities_Number 199
using namespace std;
#define route_MAX 1975
#define ERROR -1

City_Graph Read_City_CSV()
{
    City_Graph Graph;
    ifstream _infile_Cities;
    _infile_Cities.open("/Users/huang/Xcode/OOC/City_Graph/alg-2021/cities.csv",ios::in);
    if (!_infile_Cities.is_open())
    {
        cout<<"OPEN_ERROR_<cities.CSV>"<<endl;  //如果打开文件失败，输出这句话提示cities读取失败
        return Graph;
    }
    for (int i = 0; i<Cities_Number; i++)
    {

        //读国家和城市
        string S_line;
        getline(_infile_Cities,S_line);
        std::stringstream iss(S_line);
        string col;
        std::getline(iss, col, ',');
        Graph.City_location[i].nation = col;
        std::getline(iss, col, ',');
        Graph.City_location[i].city = col;
        //读经纬度
        iss>>Graph.City_location[i].longitude;
        std::getline(iss, col, ',');
        iss>>Graph.City_location[i].latitude;
    }
    _infile_Cities.close();
    return Graph;
}


int main()
{
    City_Graph CtoC_Graph = Read_City_CSV();
    int i;
    CtoC_Graph.Read_and_create_Routes_Graph();
    CtoC_Graph.Floyd_time();
    CtoC_Graph.Floyd_money();
    int continue_toll = 1;
    int Ele_toll = 1;
    
    CtoC_Graph.BFSTraverse();//遍历
    
    CtoC_Graph.Client();
    return 0;
}
