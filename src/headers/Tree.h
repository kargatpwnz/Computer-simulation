//
// Created by na1l on 22.02.18.
//

#ifndef MODELING_TREE_H
#define MODELING_TREE_H

#include <vector>
#include <map>

class Tree {

 public:
  Tree(int vertexCount, int degree);

  virtual ~Tree();

  void SetRoot();

  void PrintTree();

  void GenerateTree();
 protected:
  std::vector<int> vertexes_;

  std::map<int, int> vertex_pow_pair_;
  std::map<int, std::vector<int>> tree_;

  int root_;
  int max_degree_;
};

#endif //MODELING_TREE_H
