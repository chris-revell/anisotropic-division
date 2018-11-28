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

void CalculateForces(std::vector<cell>& Cells,const arma::mat& gridcount,const arma::cube& gridcells,const float& griddim,const int& Ng,const int& Nc,const float& cellcycletime,const float& cellradius,const float& dt);

#endif /* CalculateForces_hpp */
