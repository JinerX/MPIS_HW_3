//
// Created by JS on 24.11.2024.
//

#include <tuple>
#include <vector>
#include <random>
#include "../include/experiments.h"

#include <algorithm>
#include <iostream>
#include <ostream>


Simulation singleSimulation(int n, double p) {
    int everyRec=0;
    int num_empty=n;

    int counter = 0;

    std::vector<int> receivers(n,0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);

    while (everyRec == 0) {
        counter++;
        for (int i = 0; i <= n-1; i++) {
            double num = dist(gen);
            if (num < p) {
                if (receivers[i] == 0) {
                    num_empty --;
                }
                receivers[i] ++;
            }
        }
        if (num_empty == 0) {
            everyRec = counter;
        }
    }

    const Simulation simulation(everyRec, n);
    return simulation;
}

std::tuple<std::vector<Simulation>,std::vector<AvgSimulation>> batch_simulation(int n_max,int n_min,int n_int,double p,int k) {
    std::vector<Simulation> sims;
    std::vector<AvgSimulation> avgSims;

    for(int n=n_min; n<=n_max; n=n+n_int) {
        std::cout << n << std::endl;

        double avgEveryRec = 0;

        for(int i=0;i<k;i++) {
            Simulation sim = singleSimulation(n,p);
            avgEveryRec += sim.everyRec;
            sims.push_back(sim);
        }

        avgEveryRec = avgEveryRec/k;
        AvgSimulation avgSim(avgEveryRec,n);
        avgSims.push_back(avgSim);
    }
    return {sims,avgSims};
}

