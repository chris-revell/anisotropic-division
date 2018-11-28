//
//  MorseForce.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 27/11/2018.
//
//

#include <MorseForce.hpp>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

// Subroutine to calculate the force exerted by the Morse potential between two given cells.
void MorseForce(cell& Cell1,cell& Cell2,const float& cellcycletime,const float& cellradius){
  float dx,dy,r,F,vx,vy;
  float De    = 1;            // Morse potential parameters
  float a     = 1;            // Morse potential parameters
  //float re0   = 2*cellradius; // Equilibrium separation of 2 cells at initial size = 2* initial cell radius
  float re;                   // Equilibrium separation of Cell1 and Cell2 at current ages.
  float gamma = 1;            // Drag factor
  float expfactor;            // Component of Morse potential

  re = cellradius*(sqrt(cellcycletime+Cell1.age)+sqrt(cellcycletime+Cell2.age))/sqrt(cellcycletime);

  // Calculate x and y displacements between the 2 given cells
  dx = Cell1.pos(0) - Cell2.pos(0);
  dy = Cell1.pos(1) - Cell2.pos(1);
  // Calculate distance between cells from x and y displacements
  r = sqrt(pow(dx,2)+pow(dy,2));
  // Use distance to evaluate derivative of Morse potential to give force F
  expfactor = exp(-a*(r-re));
  F = 2*a*De*(expfactor-pow(expfactor,2));
  // Overdamped Langevin => velocity = drag factor * force
  vx = gamma*F*dx/r;
  vy = gamma*F*dy/r;
  Cell1.v(0) = Cell1.v(0)-vx; // Velocity components from forces between different cells sum linearly
  Cell1.v(1) = Cell1.v(1)-vy;
  Cell2.v(0) = Cell2.v(0)+vx;
  Cell2.v(1) = Cell2.v(1)+vy;
}
