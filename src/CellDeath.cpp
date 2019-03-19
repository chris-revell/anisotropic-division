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
	int numberToErase = 0;
	vector<int> indicesToErase;

	for (int ii=0; ii<Nc; ii++){	
		currentRandomNumber = unif(rng);	
		if (currentRandomNumber < 0.5*dt/cellcycletime){
			indicesToErase.push_back(ii);
			numberToErase++;
		}
	}

	if (numberToErase > 0){
		for (int jj = numberToErase-1; jj>=0; jj--){				
			Cells.erase(Cells.begin()+indicesToErase[jj]);
		}
	}else{}

	Nc = Cells.size();
	
}