//
// Created by na1l on 22.02.18.
//

#include "tree.h"
#include <algorithm>
#include <random>
#include <iostream>

Tree::Tree(int vertexCount, int degree) {
  max_degree_ = degree;
  for (int i = 0; i < vertexCount; ++i) {
    vertexes_.push_back(i + 1);
  }
  GenerateTree();
}

Tree::~Tree()
= default;

void Tree::SetRoot() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(vertexes_.begin(), vertexes_.end(), gen);

  root_ = vertexes_.back();
  vertex_pow_pair_[root_] = 0;
  vertexes_.pop_back();
  std::cout << "Root " << root_ << std::endl;
}

void Tree::PrintTree() {
  for (auto x : tree_) {
    std::cout << x.first << " ";
    for (auto y : x.second) {
      std::cout << y << " ";
    }
    std::cout << std::endl;
  }
}

void Tree::GenerateTree() {
  SetRoot();

  while (!vertexes_.empty()) {
    int vertex = vertexes_.back();
    vertexes_.pop_back();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, vertex_pow_pair_.size());

    auto mapIt = vertex_pow_pair_.begin();
    do {
      mapIt = vertex_pow_pair_.begin();
      std::advance(mapIt, dist(gen));
    } while (mapIt == vertex_pow_pair_.end());

    int vertexInTree = mapIt->first;

    vertex_pow_pair_.insert(std::make_pair(vertex, 0));
    vertex_pow_pair_[vertex]++;
    vertex_pow_pair_[vertexInTree]++;

    if (vertex_pow_pair_[vertex] == max_degree_)
      vertex_pow_pair_.erase(vertex);
    if (vertex_pow_pair_[vertexInTree] == max_degree_)
      vertex_pow_pair_.erase(vertexInTree);

    if (vertex > vertexInTree)
      std::swap(vertex, vertexInTree);

    if (tree_[vertex].empty())
      tree_[vertex] = std::vector<int>({});

    tree_[vertex].push_back(vertexInTree);
  }
}
