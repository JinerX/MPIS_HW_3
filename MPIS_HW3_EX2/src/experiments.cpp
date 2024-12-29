//
// Created by JS on 24.11.2024.
//

#include <tuple>
#include <vector>
#include <random>
#include "../include/experiments.h"

#include <algorithm>

std::vector<int> permutation(int n) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> result(n);

    for(int i = 0; i <n; i++ ) {
        result[i] = i+1;
    }

    std::shuffle(result.begin(), result.end(), gen);

    return result;
}

Simulation singleSimulation(int n) {
    int cmprs=0;
    int relocs=0;

    std::vector<int> perm = permutation(n);

    //InsertionSort
    for(int j = 1; j < n; j++) {
        int key = perm[j];
        int i = j-1;
        while(i>=0) {
            cmprs++;
            if (perm[i]<=key) {
                i--;
                break;
            }
            perm[i+1] = perm[i];
            relocs++;
            i--;
        }
        perm[i+1] = key;
        relocs++;
    }
    const Simulation simulation(relocs, cmprs, n);
    return simulation;
}

std::tuple<std::vector<Simulation>,std::vector<AvgSimulation>> batch_simulation(int n_max,int n_min,int n_int,int k) {
    std::vector<Simulation> sims;
    std::vector<AvgSimulation> avgSims;

    for(int n=n_min; n<=n_max; n=n+n_int) {

        double avg_relocs = 0;
        double avg_cmprs = 0;

        for(int i=0;i<k;i++) {
            Simulation sim = singleSimulation(n);
            avg_relocs += sim.relocs;
            avg_cmprs += sim.cmprs;
            sims.push_back(sim);
        }

        avg_relocs = avg_relocs/k;
        avg_cmprs = avg_cmprs/k;
        AvgSimulation avgSim(avg_relocs,avg_cmprs,n);
        avgSims.push_back(avgSim);
    }
    return {sims,avgSims};
}

