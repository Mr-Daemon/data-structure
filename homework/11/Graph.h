/*******************************************************************************
* FileName:         Graph.h
* Author:           Name
* Student Number:   Student_id
* Date:             2020/04/22 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #11
*******************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <cstring>
#include <iostream>

class Graph {
private:
    struct Node {
        int v;
        int w;
        Node *next;

        Node() { this->next = nullptr; }

        Node(int v, int w) {
            this->v = v;
            this->w = w;
            this->next = nullptr;
        };
    };

    Node **graph;
    int max_v;
    int edge_num;
public:
    struct Edge {
        int s, t, w;
    };
    /**
     *  类的构造函数
        @name Graph(int)
        @param  arg1 最大的定点数
        @return  
    */
    explicit Graph(int max_v);

    /**
     *  类的析构函数
        @name ~Graph()
        @param 
        @return 
    */
    ~Graph();

    /**
     *  向图中加入(s, t)， 权重为w的双向边
        @name addEdge(int, int, int)
        @param  arg1 边的顶点1
        @param  arg2 边的顶点2
        @param  arg3 边的权重
        @return  void
    */
    void addEdge(int s, int t, int w);

    int searchPath(int origin, int dest, const int *pass, int n1, const int *avoid, int n2, int *path, int num,
                   bool *reachList);
    void printPath(int origin, int dest, const int *pass, int n1, const int *avoid, int n2, int *path, int num,
                    bool *reachList);
    /**
     *  询问这张图的最小生成树(prim算法实现)
        @name int prim()
        @param
        @return  int 最小生成树的权值
    */
    int prim(Edge *list);

    /**
     *  询问这张图的最小生成树(kruskal实现)
        @name int kruskal()
        @param 
        @return  int 最小生成树的权值
    */
    int kruskal(Edge *list);
};

#endif