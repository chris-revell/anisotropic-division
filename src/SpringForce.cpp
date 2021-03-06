//
//  SpringForce.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 12/03/2019.
//
//

#include <SpringForce.hpp>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

// Subroutine to calculate the force exerted by the Morse potential between two given cells.
// Equilibrium radius for interaction between cells increases with age of both cells assuming linear growth of cell volume and corresponding increase in typical radius.
void SpringForce(cell& Cell1,cell& Cell2,const float& k, const float& gamma,const float& interactionthreshold){

  vec dx = vec(2,fill::zeros);
  vec v = vec(2,fill::zeros);
  vec F = vec(2,fill::zeros);
  float r;
  float re;                   // Equilibrium separation of Cell1 and Cell2 at current ages.

  // Calculate equilibrium radius given ages of two cells.
  Cell1.currentRadius();
  Cell2.currentRadius();
  re = Cell1.cellradius + Cell2.cellradius;

  // Calculate displacement between the 2 given cells
  dx = Cell1.pos - Cell2.pos;
  // Calculate distance between cells from x and y displacements
  r = sqrt(dot(dx,dx));

  // If the cells are separated by more than 1.1* the equilibrium radius, no force will exist between them.
  if (r>interactionthreshold*re){
  }
  else{
    // Use distance to evaluate derivative of Morse potential to give force F
    F = 0.5*k*(r-re)*dx/r;

    // Calculate velocity components from force.
    // Overdamped Langevin => velocity = force/drag factor
    v = F/gamma;

    // Velocity components from forces between different cells sum linearly
    Cell1.v = Cell1.v-v;
    Cell2.v = Cell2.v+v;
  }
}
