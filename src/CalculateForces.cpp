//
//  CalculateForces.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 28/11/2018.
//
//

#include <CalculateForces.hpp>
#include <cell.hpp>
#include <vector>
#include <armadillo>
#include <SpringForce.hpp>

using namespace std;
using namespace arma;

void CalculateForces(vector<cell>& Cells,std::vector<std::size_t>& triangles, const int& Nc,const float& dt,const float& k, const float& gamma,const float& interactionthreshold){


  for(std::size_t i = 0; i < triangles.size(); i+=3) {
    cell& a = Cells[triangles[i]];
    cell& b = Cells[triangles[i+1]];
    cell& c = Cells[triangles[i+2]];

    SpringForce(a,b,k,gamma,interactionthreshold);
    SpringForce(b,c,k,gamma,interactionthreshold);
    SpringForce(c,a,k,gamma,interactionthreshold);

  }
}
