//
// Created by cyb12 on 2020/3/2.
//

#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H
template<typename T>
struct Edge {
    int i, j;
    T t;
};

template<typename T>
class Graph {
public:
    virtual int getVerticesNum() = 0;
    virtual int getEdgesNum() = 0;
    virtual void insertEdge(Edge<T>) = 0;
    virtual void deleteEdge(int, int) = 0;
    virtual int degree(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
};

#endif //DATA_STRUCTURE_GRAPH_H
