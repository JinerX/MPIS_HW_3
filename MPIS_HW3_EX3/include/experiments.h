//
// Created by JS on 24.11.2024.
//
#include <tuple>
#include <string>
#include <vector>

#ifndef MPISBALLSANDBINS_EXPERIMENTS_H
#define MPISBALLSANDBINS_EXPERIMENTS_H


template <typename T>
struct GenericSimulation {
    T everyRec;
    int n;

    GenericSimulation(T everyRec, int n) {
        this->everyRec = everyRec;
        this->n = n;
    }
};

using Simulation = GenericSimulation<int>;
using AvgSimulation = GenericSimulation<double>;

Simulation singleSimulation(int n, double p);
std::tuple<std::vector<Simulation>,std::vector<AvgSimulation>> batch_simulation(int n_max,int n_min,int n_int, double p,int k);

#endif //MPISBALLSANDBINS_EXPERIMENTS_H
