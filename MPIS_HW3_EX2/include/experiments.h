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
    T relocs;
    T cmprs;
    int n;

    GenericSimulation(T relocs, T cmprs,int n) {
        this->relocs = relocs;
        this->cmprs = cmprs;
        this->n = n;
    }
};

using Simulation = GenericSimulation<int>;
using AvgSimulation = GenericSimulation<double>;

Simulation singleSimulation(int n);
std::tuple<std::vector<Simulation>,std::vector<AvgSimulation>> batch_simulation(int n_max,int n_min,int n_int,int k);
std::vector<int> permutation(int n);

#endif //MPISBALLSANDBINS_EXPERIMENTS_H
