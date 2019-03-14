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
#include <cell.hpp>
#include <vector>
#include <armadillo>
#include <SpringForce.hpp>

// Subroutine to identify neighbouring cells and calculate forces between them.
void CalculateForces(std::vector<cell>& Cells,std::vector<std::size_t>& triangles,const int& Nc,const float& dt,const float& k, const float& gamma,const float& interactionthreshold);

#endif /* CalculateForces_hpp */
