//
//  Noise
//  anisotropic-division
//
//  Created by Christopher Revell on 14/03/19.
//
//

#include <CalculateNoise.hpp>
#include <armadillo>
#include <random>
#include <chrono>
#include <cell.hpp>
#include <vector>

using namespace std;
using namespace arma;

void CalculateNoise(vector<cell>& Cells, const float& zeta_mag, const float& gamma){

	float mean = 0.0;
	float stddev = 1;
	vec zeta = vec(2,fill::zeros);                // Vector for stochastic component
	std::default_random_engine generator;
	std::normal_distribution<double> dist(mean, stddev);
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

	for (int ii=0;ii<Cells.size();ii++){
	  currentRandomNumber = unif(rng);
	  zeta(0) = cos(2*M_PI*currentRandomNumber);
	  zeta(1) = sin(2*M_PI*currentRandomNumber);
		Cells[ii].v = Cells[ii].v + zeta_mag*abs(dist(generator))*zeta/gamma;
	}
}
