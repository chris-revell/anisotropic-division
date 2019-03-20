//
//  Noise
//  anisotropic-division
//
//  Created by Christopher Revell on 14/03/19.
//
//

#ifndef NOISE_HPP
#define NOISE_HPP


#include <armadillo>
#include <random>
#include <chrono>
#include <cell.hpp>
#include <vector>

void CalculateNoise(std::vector<cell>& Cells, const float& zeta_mag, const float& gamma);


#endif
