//
// Created by cyb12 on 2020/3/4.
//

#ifndef DATA_STRUCTURE_ADJACENCYWDIGRAPH_H
#define DATA_STRUCTURE_ADJACENCYWDIGRAPH_H

#include <cstdlib>
#include <cstring>
#include "Graph.h"

template<typename T>
class AdjacencyWDigraph : public Graph<T> {
    int verticesNum;
    T **matrix;

    int degree(int i) override {};

public:
    AdjacencyWDigraph(int verticesNum, T *edges) : verticesNum(verticesNum) {
        auto array = (T *) malloc(verticesNum * verticesNum * sizeof(T));
        memcpy(array, edges, verticesNum * verticesNum * sizeof(T));
        matrix = (T **) malloc(verticesNum * sizeof(T *));
        for (int i = 0; i < verticesNum; ++i) {
            matrix[i] = array + verticesNum * i;
        }
    }

    int getVerticesNum() override {
        return verticesNum;
    }

    int getEdgesNum() override {
        int num = 0;
        for (int i = 0; i < verticesNum; ++i) {
            for (int j = 0; j < verticesNum; ++j) {
                if (!matrix[i][j])num++;
            }
        }
        return num;
    }

    void insertEdge(Edge<T> edge) override {
        matrix[edge.i][edge.j] = edge.t;
    }

    void deleteEdge(int i, int j) override {
        matrix[i][j] = 0;
    }


    int inDegree(int i) override {
        int num = 0;
        for (int j = 0; j < verticesNum; ++j) {
            if (!matrix[j][i])num++;
        }
        return num;
    }

    int outDegree(int i) override {
        int num = 0;
        for (int j = 0; j < verticesNum; ++j) {
            if (!matrix[i][j])num++;
        }
        return num;
    }

    //bfs, dfs要求reach全为0
    virtual void bfs(int i, bool *reach) {
        int queue[verticesNum];
        int front = 0, rear = 1;
        queue[0] = i;
        while (front != rear) {
            int current = queue[front];
            for (int j = 0; j < verticesNum; ++j) {
                if (matrix[i][j] && !reach[j]) {
                    reach[j] = true;
                    queue[rear++] = j;
                }
            }
            front++;
        }
    }

    virtual void dfs(int i, bool *reach) {
        reach[i] = true;
        for (int j = 0; j < verticesNum; ++j) {
            if (matrix[i][j] && !reach[j]) {
                dfs(j, reach);
            }
        }
    }
};


#endif //DATA_STRUCTURE_ADJACENCYWDIGRAPH_H
