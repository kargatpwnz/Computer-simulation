//
// Created by na1l on 26.02.18.
//

#include "chain.h"

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

#include <iostream>
#include <random>

Chain::Chain() {
  transition_matrix_.resize(5, 5);
  probability_sum_matrix_.resize(5, 5);
  transition_matrix2_.resize(5, 5);
  probability_sum_matrix2_.resize(5, 5);

  SetTransitionMatrices();
}

Chain::~Chain() {

}

void Chain::SetTransitionMatrices() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> double_distr(0, 1);
  std::uniform_int_distribution<> int_distr(1, 1000);

  // First matrix
  for (int i = 0; i < transition_matrix_.size1(); ++i) {
    int sum = 0;
    std::vector<double> random_numbers;

    for (int j = 0; j < transition_matrix_.size2(); ++j) {
      int random_number = int_distr(gen);
      sum += random_number;
      random_numbers.push_back(random_number);
    }

    double probability_sum = 0;
    for (int k = 0; k < transition_matrix_.size2(); ++k) {
      transition_matrix_(i, k) = random_numbers[k] / sum;
      probability_sum += transition_matrix_(i, k);
      probability_sum_matrix_(i, k) = probability_sum;
    }
  }

  // Second matrix
  std::vector<double> v1 = {0.116135, 0.205425, 0.22464, 0.182537, 0.271263};
  std::vector<double> v2 = {0.205425, 0.22464, 0.182537, 0.271263, 0.116135};
  std::vector<double> v3 = {0.22464, 0.182537, 0.271263, 0.116135, 0.205425};
  std::vector<double> v4 = {0.182537, 0.271263, 0.116135, 0.205425, 0.22464};
  std::vector<double> v5 = {0.271263, 0.116135, 0.205425, 0.22464, 0.182537};

//  std::vector<double> v1 = {0.2, 0.2, 0.4, 0.2, 0.0};
//  std::vector<double> v2 = {0.4, 0.2, 0.2, 0.0, 0.2};
//  std::vector<double> v3 = {0.2, 0.2, 0.0, 0.1, 0.5};
//  std::vector<double> v4 = {0.2, 0.0, 0.4, 0.3, 0.1};
//  std::vector<double> v5 = {0.0, 0.4, 0.0, 0.4, 0.2};

  for (int i = 0; i < 5; ++i) {
    transition_matrix2_(0, i) = v1[i];
    transition_matrix2_(1, i) = v2[i];
    transition_matrix2_(2, i) = v3[i];
    transition_matrix2_(3, i) = v4[i];
    transition_matrix2_(4, i) = v5[i];
  }

  for (int i = 0; i < transition_matrix2_.size1(); ++i) {
    double probability_sum = 0;
    for (int j = 0; j < transition_matrix2_.size2(); ++j) {
      probability_sum += transition_matrix2_(i, j);
      probability_sum_matrix2_(i, j) = probability_sum;
    }
  }
}

void Chain::PrintTransitionMatrices() {
  std::cout << std::endl << "First matrix" << std::endl;
  for (int i = 0; i < 5; ++i)
    std::cout << transitions_count_[i] / 10000.0 << " ";

  std::cout << std::endl;
  for (int i = 0; i < transition_matrix_.size1(); ++i) {
    for (int j = 0; j < transition_matrix_.size2(); j++) {
      std::cout << transition_matrix_(i, j) << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl << "Second matrix" << std::endl;
  for (int i = 0; i < 5; ++i)
    std::cout << transitions_count2_[i] / 10000.0 << " ";
  std::cout << std::endl;

  for (int i = 0; i < transition_matrix2_.size1(); ++i) {
    for (int j = 0; j < transition_matrix2_.size2(); j++) {
      std::cout << transition_matrix2_(i, j) << " ";
    }
    std::cout << std::endl;
  }

}

void Chain::GenerateTransitions() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> double_distr(0, 1);

  // First matrix
  int line = 3;
  for (int i = 0; i < 10000; ++i) {
    double ksi = double_distr(gen);

    for (int j = 0; j < probability_sum_matrix_.size2(); ++j) {
      if (ksi < probability_sum_matrix_(line, j)) {
        transitions_count_[j]++;
        line = j;
        break;
      }
    }
  }

  // Second matrix
  line = 3;
  for (int i = 0; i < 10000; ++i) {
    double ksi = double_distr(gen);

    for (int j = 0; j < probability_sum_matrix2_.size2(); ++j) {
      if (ksi < probability_sum_matrix2_(line, j)) {
        transitions_count2_[j]++;
        line = j;
        break;
      }
    }
  }
}

void Chain::MultiplyMatrices() {
  for (int i = 0; i < 30; ++i)
    transition_matrix_ = boost::numeric::ublas::prod(
        transition_matrix_, transition_matrix_);

  for (int i = 0; i < 30; ++i)
    transition_matrix2_ = boost::numeric::ublas::prod(
        transition_matrix2_, transition_matrix2_);
}
