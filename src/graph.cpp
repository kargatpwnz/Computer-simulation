//
// Created by na1l on 25.02.18.
//

#include <algorithm>
#include <iostream>
#include <random>
#include "graph.h"

Graph::Graph(int vertex_count, int edges, int degree) : Tree(vertex_count, degree) {
  if ((vertex_count * (vertex_count - 1) / 2) < edges)
    throw -1;
  if (vertex_count - 1 > edges)
    throw -2;
  if (degree == 1 || degree == 0)
    throw -3;
  if (degree <= 2 * edges / vertex_count)
    throw -3;

  vertex_count_ = vertex_count;
  edges_count_ = edges;
  max_degree_ = degree;
}

Graph::~Graph()
= default;

void Graph::GenerateGraph() {
  for (int i = 0; i < (edges_count_ - (vertex_count_ - 1)); ++i) {
    auto twoVertex = GetTwoRandVertex();

    auto itBegin = tree_[twoVertex[0]].begin();
    auto itEnd = tree_[twoVertex[0]].end();
    while (std::find(itBegin, itEnd, twoVertex[1]) != itEnd) {
      twoVertex = GetTwoRandVertex();
      itBegin = tree_[twoVertex[0]].begin();
      itEnd = tree_[twoVertex[0]].end();
    }
    vertex_pow_pair_[twoVertex[0]]++;
    vertex_pow_pair_[twoVertex[1]]++;

    tree_[twoVertex[0]].push_back(twoVertex[1]);

    if (vertex_pow_pair_[twoVertex[0]] == max_degree_)
      vertex_pow_pair_.erase(twoVertex[0]);
    if (vertex_pow_pair_[twoVertex[1]] == max_degree_)
      vertex_pow_pair_.erase(twoVertex[1]);

  }
}

std::vector<int> Graph::GetTwoRandVertex() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, vertex_pow_pair_.size());

  int vertex1 = 0;
  int vertex2 = 0;
  do {
    auto mapIt = vertex_pow_pair_.begin();
    do {
      mapIt = vertex_pow_pair_.begin();
      std::advance(mapIt, dist(gen));
    } while (mapIt == vertex_pow_pair_.end());
    vertex1 = mapIt->first;

    mapIt = vertex_pow_pair_.begin();
    do {
      mapIt = vertex_pow_pair_.begin();
      std::advance(mapIt, dist(gen));
    } while (mapIt == vertex_pow_pair_.end());
    vertex2 = mapIt->first;
  } while (vertex1 == vertex2);

  if (vertex1 > vertex2)
    std::swap(vertex1, vertex2);

  return std::vector<int>({vertex1, vertex2});
}
