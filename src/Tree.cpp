//
// Created by na1l on 22.02.18.
//

#include "headers/Tree.h"
#include <algorithm>
#include <random>
#include <iostream>

Tree::Tree(int vertexCount, int degree)
{
    maxDegree = degree;
    for (int i = 0; i < vertexCount; ++i) {
        vertexes.push_back(i + 1);
    }
    generateTree();
}

Tree::~Tree()
= default;

void Tree::setRoot()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(vertexes.begin(), vertexes.end(), gen);

    root = vertexes.back();
    vertexPowPair[root] = 0;
    vertexes.pop_back();
    std::cout << "Root " << root << std::endl;
}

void Tree::printTree()
{
    for (auto x : tree) {
        std::cout << x.first << " ";
        for (auto y : x.second) {
            std::cout << y <<  " ";
        }
        std::cout << std::endl;
    }
}

void Tree::generateTree()
{
    setRoot();

    while (!vertexes.empty()) {
        int vertex = vertexes.back();
        vertexes.pop_back();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, vertexPowPair.size());

        auto mapIt = vertexPowPair.begin();
        do {
            mapIt = vertexPowPair.begin();
            std::advance(mapIt, dist(gen));
        } while (mapIt == vertexPowPair.end());

        int vertexInTree = mapIt->first;

        vertexPowPair.insert(std::make_pair(vertex, 0));
        vertexPowPair[vertex]++;
        vertexPowPair[vertexInTree]++;

        if (vertexPowPair[vertex] == maxDegree)
            vertexPowPair.erase(vertex);
        if (vertexPowPair[vertexInTree] == maxDegree)
            vertexPowPair.erase(vertexInTree);

        if (vertex > vertexInTree)
            std::swap(vertex, vertexInTree);

        if (tree[vertex].empty())
            tree[vertex] = std::vector<int>({});

        tree[vertex].push_back(vertexInTree);
    }
}
