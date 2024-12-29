#include <iostream>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "experiments.h"
#include "plots.h"
#include "funcWrapper.h"


int main() {
    int d_max = 2;
    for(int d = 1; d <= d_max; d++) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto [sims,avg_sims] = batch_simulation_d_rep(1000000,10000,10000,50,d);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds >(end - begin).count() << "[s]" << std::endl;

        //Split by values
        std::vector<int> first_collisions;
        std::vector<int> all_non_emptys;
        std::vector<int> all_twos;
        std::vector<int> empty_after_ns;
        std::vector<int> numBinss;
        std::vector<int> max_after_ns;

        for(Simulation sim : sims) {
            first_collisions.push_back(sim.first_collision);
            all_non_emptys.push_back(sim.all_non_empty);
            all_twos.push_back(sim.all_two);
            empty_after_ns.push_back(sim.empty_after_n);
            numBinss.push_back(sim.numBins);
            max_after_ns.push_back(sim.max_after_n);
        }

        std::vector<double> avgFirst_collisions;
        std::vector<double> avgAll_non_emptys;
        std::vector<double> avgAll_twos;
        std::vector<double> avgEmpty_after_ns;
        std::vector<double> avgNumBinss;
        std::vector<double> avgMaxAfter_ns;
        for(AvgSimulation avgSim : avg_sims){
            avgFirst_collisions.push_back(avgSim.first_collision);
            avgAll_non_emptys.push_back(avgSim.all_non_empty);
            avgAll_twos.push_back(avgSim.all_two);
            avgEmpty_after_ns.push_back(avgSim.empty_after_n);
            avgNumBinss.push_back(avgSim.numBins);
            avgMaxAfter_ns.push_back(avgSim.max_after_n);
        }

        //L^1
        if (d==1) {
            make_plot(numBinss,max_after_ns,avgNumBinss,avgMaxAfter_ns,"L_n^1","L_n^1");
        }

        //L^2
        if (d==2) {
            make_plot(numBinss,max_after_ns,avgNumBinss,avgMaxAfter_ns,"L_n^2","L_n^2");
        }
        //l_n^d/(ln(n)/(ln(ln(n))))
        if (d==1) {
            createPlotlnln2(max_after_ns,numBinss,avgMaxAfter_ns,avgNumBinss,"l(n)^1_f_1(n)","l(n)^1_f_1(n)");
        }

        //l_n^d/(ln(ln(n))/ln(2))
        if (d==2) {
            createPlotln2_div_ln2(max_after_ns,numBinss,avgMaxAfter_ns,avgNumBinss,"l(n)^2_f_2(n)","l(n)^2_f_2(n)");
        }
    }
    return 0;
}
