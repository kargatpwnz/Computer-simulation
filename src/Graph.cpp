//
// Created by na1l on 25.02.18.
//

#include <algorithm>
#include <iostream>
#include <random>
#include "headers/Graph.h"

Graph::Graph(int vertexCount1, int edges, int degree) : Tree(vertexCount1, degree)
{
    if ( (vertexCount1 * (vertexCount1 - 1) / 2) < edges )
        throw -1;
    if (vertexCount1 - 1 > edges)
        throw -2;
    if (degree == 1 || degree == 0)
        throw -3;
//    if (edges - vertexCount1 <= degree)
//        throw -3;
    //TODO: degree checking

    vertexCount = vertexCount1;
    edgesCount = edges;
    maxDegree = degree;
}

Graph::~Graph()
= default;

void Graph::generateGraph()
{
    for (int i = 0; i < (edgesCount - (vertexCount - 1)); ++i) {
        auto twoVertex = getTwoRandVertex();

        auto itBegin = tree[twoVertex[0]].begin();
        auto itEnd = tree[twoVertex[0]].end();
        while (std::find(itBegin, itEnd, twoVertex[1]) != itEnd) {
            twoVertex = getTwoRandVertex();
        }
        vertexPowPair[twoVertex[0]]++;
        vertexPowPair[twoVertex[1]]++;

        tree[twoVertex[0]].push_back(twoVertex[1]);

        if (vertexPowPair[twoVertex[0]] == maxDegree)
            vertexPowPair.erase(twoVertex[0]);
        if (vertexPowPair[twoVertex[1]] == maxDegree)
            vertexPowPair.erase(twoVertex[1]);

    }
}

std::vector<int> Graph::getTwoRandVertex()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, vertexPowPair.size());

    int vertex1 = 0;
    int vertex2 = 0;
    do {
        auto mapIt = vertexPowPair.begin();
        do {
            mapIt = vertexPowPair.begin();
            std::advance(mapIt, dist(gen));
        } while (mapIt == vertexPowPair.end());
        vertex1 = mapIt->first;

        mapIt = vertexPowPair.begin();
        do {
            mapIt = vertexPowPair.begin();
            std::advance(mapIt, dist(gen));
        } while (mapIt == vertexPowPair.end());
        vertex2 = mapIt->first;
    } while (vertex1 == vertex2);

    if (vertex1 > vertex2)
        std::swap(vertex1, vertex2);

    return std::vector<int>({vertex1, vertex2});
}
