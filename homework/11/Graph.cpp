
#include "Graph.h"

Graph::Graph(int max_v) : max_v(max_v), edge_num(0) {
    graph = new Node *[max_v];
    for (int i = 0; i < max_v; i++) {
        graph[i] = nullptr;
    }
}

Graph::~Graph() {
    for (int i = 0; i < max_v; i++) {
        Node *temp = graph[i];
        Node *next = temp;
        while (next) {
            next = next->next;
            delete temp;
            temp = next;
        }
    }
    delete[] graph;
}

void Graph::addEdge(int s, int t, int w) {
    Node **node = graph + s;
    while (*node) {
        node = &((*node)->next);
    }
    *node = new Node(t, w);
    node = graph + t;
    while (*node) {
        node = &((*node)->next);
    }
    *node = new Node(s, w);
    edge_num++;
}

int Graph::searchPath(int origin, int dest, const int *pass, int n1, const int *avoid, int n2, int *path, int num,
                      bool *reachList) {
    reachList[origin] = true;
    path[num++] = origin;
    int weight = INT16_MAX;
    //get a path by recursion, check the pass point
    if (origin == dest) {
        for (int i = 0; i < n1; ++i) {
            bool flag = false;
            for (int j = 0; j < num; ++j) {
                if (path[j] == pass[i]) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                return INT16_MAX;
            }
        }
        return 0;
    }
    Node *node = graph[origin];
    //temporary store the local optimum
    int subPath[max_v];
    //traverse all possible connected path to this node
    while (node) {
        bool flag = true;
        //ensure node->v is not an avoid vertex and not reached before
        for (int i = 0; i < n2; ++i) {
            if (avoid[i] == node->v) {
                flag = false;
                break;
            }
        }
        if (reachList[node->v]) {
            flag = false;
        }
        if (flag) {
            bool subReachList[max_v];//current reach list
            memcpy(subReachList, reachList, max_v * sizeof(bool));
            int localPath[max_v];
            memcpy(localPath, path, max_v * sizeof(int));
            int path_w = node->w + searchPath(node->v, dest, pass, n1, avoid, n2, localPath, num, subReachList);
            if (weight > path_w) {
                memcpy(subPath, localPath, max_v * sizeof(int));
                weight = path_w;
            }
        }
        node = node->next;
    }
    memcpy(path, subPath, max_v * sizeof(int));
    return weight;
}

void Graph::printPath(int origin, int dest, const int *pass, int n1, const int *avoid, int n2, int *path, int num,
                      bool *reachList) {
    reachList[origin] = true;
    path[num++] = origin;
    //get a path by recursion, check the pass point
    if (origin == dest) {
        bool flag = false;
        for (int i = 0; i < n1; ++i) {
            for (int j = 0; j < num; ++j) {
                if (path[j] == pass[i]) {
                    flag = true;
                    break;
                }
            }
            if (flag && i < n1 - 1) {
                flag = false;
            } else {
                break;
            }
        }
        if (flag) {
            for (int j = 0; j < max_v; ++j) {
                if (path[j] == dest) {
                    std::cout << path[j] << "\n";
                    break;
                } else {
                    std::cout << path[j] << "->";
                }
            }
        }
    }
    Node *node = graph[origin];
    //traverse all possible connected path to this node
    while (node) {
        bool flag = true;
        //ensure node->v is not an avoid vertex and not reached before
        for (int i = 0; i < n2; ++i) {
            if (avoid[i] == node->v) {
                flag = false;
                break;
            }
        }
        if (reachList[node->v]) {
            flag = false;
        }
        if (flag) {
            bool subReachList[max_v];//current reach list
            memcpy(subReachList, reachList, max_v * sizeof(bool));
            int localPath[max_v];
            memcpy(localPath, path, max_v * sizeof(int));
            printPath(node->v, dest, pass, n1, avoid, n2, localPath, num, subReachList);
        }
        node = node->next;
    }
}


int Graph::prim(Edge *list) {
    bool selectList[max_v];
    memset(selectList, 0, max_v * sizeof(bool));
    selectList[0] = true;
    int weight = 0;
    int cur = 0;
    for (int num = 0; num < max_v; num++) {
        Node *min_node = nullptr;
        int index = -1;
        for (int i = 0; i < max_v; i++) {
            if (selectList[i]) {
                Node *node = graph[i];
                while (node) {
                    if (!selectList[node->v] && (!min_node || node->w < min_node->w)) {
                        min_node = node;
                        index = i;
                    }
                    node = node->next;
                }
            }
        }
        selectList[min_node->v] = true;
        weight += min_node->w;
        if (index < min_node->v) {
            list[cur++] = {index, min_node->v, min_node->w};
        } else {
            list[cur++] = {min_node->v, index, min_node->w};
        }
    }
    return weight;
}

int Graph::kruskal(Edge *list) {
    int weight = 0;
    Edge edge_list[edge_num];
    int num = 0;
    for (int i = 0; i < max_v; ++i) {
        Node *node = graph[i];
        while (node) {
            int j = 0;
            while (j < num && edge_list[j].w <= node->w) {
                if (i == edge_list[j].t && node->v == edge_list[j].s) goto go_next;
                j++;
            }
            for (int k = num - 1; k >= j; --k) {
                edge_list[k + 1] = edge_list[k];
            }
            edge_list[j] = {i, node->v, node->w};
            num++;
            go_next:
            node = node->next;
        }
    }
    bool selectList[max_v];
    memset(selectList, false, max_v * sizeof(bool));
    int cur = 0;
    for (int l = 0; l < edge_num; ++l) {
        if (!(selectList[edge_list[l].s] && selectList[edge_list[l].t])) {
            selectList[edge_list[l].s] = true;
            selectList[edge_list[l].t] = true;
            weight += edge_list[l].w;
            list[cur++] = edge_list[l];
        }
    }
    return weight;
}

int Graph::getV() {
    return max_v;
}

bool Graph::connect(int origin, int dest) {
    bool reachList[max_v];
    memset(reachList, 0, max_v * sizeof(bool));
    connect(origin, reachList);
    return reachList[dest];
}

void Graph::connect(int origin, bool *reachList) {
    if (!reachList[origin]) {
        reachList[origin] = true;
        Node *node = graph[origin];
        while (node) {
            if (!reachList[node->v]) {
                connect(node->v, reachList);
            }
            node = node->next;
        }
    }
}

int *Graph::dijkstra() {
    int *result = new int[max_v + 1];
    for (int i = 1; i < max_v; ++i) {
        if (connect(0, i)) {
            int placeHolder[max_v];
            bool reachList[max_v];
            memset(reachList, 0, max_v * sizeof(bool));
            result[i + 1] = searchPath(0, i, nullptr, 0, nullptr, 0, placeHolder, 0, reachList);
        } else {
            result[i + 1] = -1;
        }
    }
    return result;
}



