//
// Created by na1l on 21.02.18.
//

#include <iostream>
#include <fstream>
#include <random>
#include "headers/Selection.h"

Selection::Selection()
{
    fillVectors();
}

Selection::~Selection()
= default;

void Selection::fillVectors()
{
    for (int i = 0; i < numCount; ++i) {
        numbers.push_back(i + 1);
        sum += i;
    }

    for (auto num : numbers) {
        chances.push_back((double) num / sum);
    }

    double s = 0;
    for (double chance : chances) {
        s += chance;
        chancesSum.push_back(s);
    }
}

void Selection::selectionWithReturn()
{
    std::ofstream file;
    file.open("/home/na1l/CLionProjects/ComputerSimulation/withReturn.txt");

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);

    for (int i = 0; i < numTries; ++i) {
        double ksi = distribution(generator);
        std::cout << ksi << std::endl;

        for (int j = 0; j < numCount; ++j) {
            if (ksi < chancesSum[j]) {
                file << numbers[j] << std::endl;
                break;
            }
        }
    }
    file.close();
}

void Selection::selectionWOReturn()
{
    std::ofstream file;
    file.open("/home/na1l/CLionProjects/ComputerSimulation/WO_Return_90000.txt", std::ofstream::app);

    for (int i = 0; i < 9; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, chancesSum.back());
        double ksi = dis(gen);

        for (int j = 0; j < numbers.size(); ++j) {
            if (ksi < chancesSum[j]) {
                file << numbers[j] << std::endl;

                numbers.erase(numbers.begin() + j);
                chances.erase(chances.begin() + j);
                chancesSum.clear();

                double s = 0;
                for (double chance : chances) {
                    s += chance;
                    chancesSum.push_back(s);
                }
                break;
            }
        }
    }
    file.close();
}
