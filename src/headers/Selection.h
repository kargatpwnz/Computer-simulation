//
// Created by na1l on 21.02.18.
//

#ifndef MODELING_DISTRIBUTION_H
#define MODELING_DISTRIBUTION_H

#include <vector>

class Selection {
    std::vector<int> numbers;
    std::vector<double> chances;
    std::vector<double> chancesSum;
    int numTries = 10000;
    int numCount = 10;
    int sum = 0;
public:
    Selection();

    virtual ~Selection();

    void fillVectors();

    void selectionWithReturn();

    void selectionWOReturn();

};

#endif //MODELING_DISTRIBUTION_H
