//
//  CalculateForces.hpp
//  anisotropic-division
//
//  Created by Christopher Revell on 28/11/2018.
//
//

#ifndef CalculateForces_hpp
#define CalculateForces_hpp

#include <cell.hpp>
#include <vector>
#include <PositionToIndex.hpp>
#include <armadillo>
#include <MorseForce.hpp>

// Subroutine to identify neighbouring cells and calculate forces between them.
void CalculateForces(std::vector<cell>& Cells,const arma::mat& gridcount,const arma::cube& gridcells,const float& griddim,const int& Ng,const int& Nc,const float& dt,const float& k, const float& gamma);

#endif /* CalculateForces_hpp */
