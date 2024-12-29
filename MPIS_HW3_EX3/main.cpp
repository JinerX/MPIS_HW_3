#include <format>
#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <cmath>
#include "experiments.h"
#include "plots.h"
#include "funcWrapper.h"

std::string double_to_percent(double x) {
    x = x * 100;
    int y = round(x);
    std::string s = std::to_string(y);
    return s;
}


int main()
{
    std::vector<double> probs = {0.5,0.1};
    for (double p : probs) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto [sims,avg_sims] = batch_simulation(10000,100,100,p,50);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds >(end - begin).count() << "[s]" << std::endl;

        std::vector<int> allEveryRecs;
        std::vector<int> allNs;
        for (Simulation sim : sims) {
            allEveryRecs.push_back(sim.everyRec);
            allNs.push_back(sim.n);
        }

        std::vector<double> avgEveryRecs;
        std::vector<double> avgNs;
        for (AvgSimulation sim : avg_sims) {
            avgEveryRecs.push_back(sim.everyRec);
            avgNs.push_back(sim.n);
        }


        std::string s = std::format("T_n_{}%",double_to_percent(p));
        // T_n
        make_plot(allNs,allEveryRecs,avgNs,avgEveryRecs,s,s);

        s = std::format("f(n)p{}%",double_to_percent(p));
        //T_n assymptotically
        createPlot_receivers(allEveryRecs,allNs,avgEveryRecs,avgNs,p,s,s);
    }
    return 0;
}
