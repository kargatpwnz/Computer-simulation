//
// Created by na1l on 21.02.18.
//

#ifndef MODELING_DISTRIBUTION_H
#define MODELING_DISTRIBUTION_H

#include <vector>

class Selection {
 public:
  Selection();

  virtual ~Selection();

  void FillVectors();

  void SelectionWithReturn();

  void SelectionWoReturn();

 private:
  std::vector<int> numbers_;
  std::vector<double> chances_;
  std::vector<double> chances_sum_;
  int num_tries_ = 10000;
  int num_count_ = 10;
  int sum_ = 0;
};

#endif //MODELING_DISTRIBUTION_H
