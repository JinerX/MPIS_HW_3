#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "experiments.h"
#include "plots.h"
#include "funcWrapper.h"
int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto [sims,avg_sims] = batch_simulation(10000,100,100,50);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds >(end - begin).count() << "[s]" << std::endl;

    std::vector<int> allRelocs;
    std::vector<int> allCmprs;
    std::vector<int> allNs;

    for (Simulation sim : sims) {
        allCmprs.push_back(sim.cmprs);
        allRelocs.push_back(sim.relocs);
        allNs.push_back(sim.n);
    }

    std::vector<double> avgAllRelocs;
    std::vector<double> avgAllCmprs;
    std::vector<double> avgAllNs;

    for (AvgSimulation avgSim : avg_sims) {
        avgAllCmprs.push_back(avgSim.cmprs);
        avgAllRelocs.push_back(avgSim.relocs);
        avgAllNs.push_back(avgSim.n);
    }

    //cmp(n)
    make_plot(allNs,allCmprs,avgAllNs,avgAllCmprs,"cmp(n)","cmp(n)");


    //s(n)
    make_plot(allNs,allRelocs,avgAllNs,avgAllRelocs,"s(n)","s(n)");

    //cmp(n)/n
    createPlotn(allCmprs,allNs,avgAllCmprs,avgAllNs,"cmp(n)_n","cmp(n)_n");

    //cmp(n)/n^2
    createPlotn2(allCmprs,allNs,avgAllCmprs,avgAllNs,"cmp(n)_n^2","cmp(n)_n^2");


    //s(n)/n
    createPlotn(allRelocs,allNs,avgAllRelocs,avgAllNs,"s(n)_n","s(n)_n");

    //s(n)/n^2
    createPlotn2(allRelocs,allNs,avgAllRelocs,avgAllNs,"s(n)_n^2","s(n)_n^2");

    return 0;
}
