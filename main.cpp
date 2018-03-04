#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "src/headers/Tree.h"
#include "src/headers/Graph.h"
#include "src/headers/Chain.h"

using namespace boost::numeric::ublas;

int main() {
  Chain chain;
  chain.MultiplyMatrices();
  chain.GenerateTransitions();
  chain.PrintTransitionMatrices();

  return 0;
}
