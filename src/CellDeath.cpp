//
//  CellDeath.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 17/03/2019.
//
//

#include "CellDeath.hpp"
#include <random>
#include <chrono>
#include <cell.hpp>
#include <vector>

using namespace std;

void CellDeath(vector<cell>& Cells, int& Nc, const float& dt, const float& cellcycletime){

	// The following 0-1 random number generator from https://stackoverflow.com/questions/9878965/rand-between-0-and-1
		std::mt19937_64 rng;
		// initialize the random number generator with time-dependent seed
		uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
		rng.seed(ss);
		// initialize a uniform distribution between 0 and 1
		std::uniform_real_distribution<double> unif(0, 1);
		double currentRandomNumber;
		// ready to generate random numbers
	//

	for (int ii; ii<Nc; ii++){	
		currentRandomNumber = unif(rng);
		if (currentRandomNumber < dt/cellcycletime){
			Cells.erase(Cells.begin()+ii);
			Nc = Nc-1;
		}
	}
}