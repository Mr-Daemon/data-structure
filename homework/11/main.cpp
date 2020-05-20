#include <iostream>
#include <cstdio>

#include "Graph.h"

using std::cin;
using std::cout;
using std::endl;

struct Edge {
    int s, t, w;
};

int main() {
    int vertices = 14;
    Graph g(vertices);
    Edge list[] = {{0,  1,  1},
                   {0,  2,  1},
                   {0,  3,  1},
                   {0,  4,  1},
                   {1,  6,  1},
                   {1,  8,  1},
                   {3,  6,  1},
                   {4,  7,  1},
                   {5,  8,  1},
                   {5,  9,  1,},
                   {6,  7,  1},
                   {6,  9,  1},
                   {7,  10, 1},
                   {7,  11, 1},
                   {8,  12, 1},
                   {9,  10, 1},
                   {9,  12, 1},
                   {10, 13, 1},
                   {11, 13, 1},
                   {12, 14, 1},
                   {13, 14, 1}};
    for (auto &i : list) {
        g.addEdge(i.s, i.t, i.w);
    }
//    Edge spanTree[vertices];
//    g.prim(reinterpret_cast<Graph::Edge *>(spanTree));
//    for (int j = 0; j < vertices; ++j) {
//        std::cout << "(" << spanTree[j].s << "," << spanTree[j].t << ")" << std::endl;
//    }
    int path[vertices];
    bool reachList[vertices];
    memset(reachList, 0, vertices * sizeof(bool));
    int origin = 14;
    int dest = 0;
    int pass[] = {12, 8};
    int avoid[] = {5, 10};
//    g.printPath(origin, dest, pass, sizeof(pass) / sizeof(int), avoid, sizeof(avoid) / sizeof(int), path,
//                 0, reachList);
    std::cout << g.connect(0, 1);
//    for (int j = 0; j < vertices; ++j) {
//        if (path[j] == dest) {
//            cout << path[j] << "\n";
//            break;
//        } else {
//            cout << path[j] << "->";
//        }
//    }
    return 0;
}