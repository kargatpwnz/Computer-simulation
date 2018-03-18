#include <iostream>
#include <queue>

#include "queueing_system.h"
#include <random>

int main() {
  QueueingSystem model(2.0, TIME_UNIFORM, TIME_CONST);
  model.PrintEventList();
  model.Start();
  std::cout << "----------------------------" << std::endl;
  model.PrintStartList();
  std::cout << model.CalculateAvgQueueingTime() << std::endl;
  return 0;
}
