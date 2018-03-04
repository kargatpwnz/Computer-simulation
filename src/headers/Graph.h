//
// Created by na1l on 25.02.18.
//

#ifndef MODELING_GRAPH_H
#define MODELING_GRAPH_H

#include "Tree.h"

class Graph : public Tree {
 public:
  Graph(int vertex_count, int degree, int edges);

  virtual ~Graph();

  void GenerateGraph();

  std::vector<int> GetTwoRandVertex();
 private:
  int vertex_count_;
  int edges_count_;
};

#endif //MODELING_GRAPH_H
