//
// Created by na1l on 21.02.18.
//

#include <iostream>
#include <fstream>
#include <random>
#include "selection.h"

Selection::Selection() {
  FillVectors();
}

Selection::~Selection()
= default;

void Selection::FillVectors() {
  for (int i = 0; i < num_count_; ++i) {
    numbers_.push_back(i + 1);
    sum_ += i;
  }

  for (auto num : numbers_) {
    chances_.push_back((double) num / sum_);
  }

  double s = 0;
  for (double chance : chances_) {
    s += chance;
    chances_sum_.push_back(s);
  }
}

void Selection::SelectionWithReturn() {
  std::ofstream file;
  file.open("/home/na1l/CLionProjects/ComputerSimulation/withReturn.txt");

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0, 1);

  for (int i = 0; i < num_tries_; ++i) {
    double ksi = distribution(generator);
    std::cout << ksi << std::endl;

    for (int j = 0; j < num_count_; ++j) {
      if (ksi < chances_sum_[j]) {
        file << numbers_[j] << std::endl;
        break;
      }
    }
  }
  file.close();
}

void Selection::SelectionWoReturn() {
  std::ofstream file;
  file.open("/home/na1l/CLionProjects/ComputerSimulation/WO_Return_90000.txt",
            std::ofstream::app);

  for (int i = 0; i < 9; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, chances_sum_.back());
    double ksi = dis(gen);

    for (int j = 0; j < numbers_.size(); ++j) {
      if (ksi < chances_sum_[j]) {
        file << numbers_[j] << std::endl;

        numbers_.erase(numbers_.begin() + j);
        chances_.erase(chances_.begin() + j);
        chances_sum_.clear();

        double s = 0;
        for (double chance : chances_) {
          s += chance;
          chances_sum_.push_back(s);
        }
        break;
      }
    }
  }
  file.close();
}
