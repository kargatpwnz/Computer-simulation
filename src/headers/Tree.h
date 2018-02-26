//
// Created by na1l on 22.02.18.
//

#ifndef MODELING_TREE_H
#define MODELING_TREE_H

#include <vector>
#include <map>

class Tree {
protected:
    std::vector<int> vertexes;

    std::map<int, int> vertexPowPair;
    std::map<int, std::vector<int>> tree;

    int root;
    int maxDegree;
public:
    Tree(int vertexCount, int degree);

    virtual ~Tree();

    void setRoot();

    void printTree();

    void generateTree();
};

#endif //MODELING_TREE_H
