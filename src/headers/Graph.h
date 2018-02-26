//
// Created by na1l on 25.02.18.
//

#ifndef MODELING_GRAPH_H
#define MODELING_GRAPH_H

#include "Tree.h"

class Graph : public Tree {
    int vertexCount;
    int edgesCount;
public:
    Graph(int vertexCount, int degree, int edges);

    virtual ~Graph();

    void generateGraph();

    std::vector<int> getTwoRandVertex();

};

#endif //MODELING_GRAPH_H
