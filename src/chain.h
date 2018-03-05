//
// Created by na1l on 26.02.18.
//

#ifndef MODELING_CHAIN_H
#define MODELING_CHAIN_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

class Chain {
 public:
  Chain();

  virtual ~Chain();

  void SetTransitionMatrices();

  void PrintTransitionMatrices();

  void GenerateTransitions();

  void MultiplyMatrices();

 private:
  boost::numeric::ublas::matrix<double> transition_matrix_;
  boost::numeric::ublas::matrix<double> transition_matrix2_;
  boost::numeric::ublas::matrix<double> probability_sum_matrix_;
  boost::numeric::ublas::matrix<double> probability_sum_matrix2_;
  std::vector<int> transitions_count_ = {0, 0, 0, 0, 0};
  std::vector<int> transitions_count2_ = {0, 0, 0, 0, 0};
};

#endif //MODELING_CHAIN_H
