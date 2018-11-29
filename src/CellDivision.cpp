//
//  CellDivision.cpp
//  anisotropic-division
//
//  Created by Christopher Revell on 27/11/2018.
//
//

#include <CellDivision.hpp>
#include <vector>
#include <cell.hpp>

using namespace std;
using namespace arma;

// Subroutine to test all cells in vector Cells and determine whether any are older than the cell cycle time.
// Any cells older than the cell cycle time undergo division. The two daughter cells have age=0
// and are always separated by 2* typical cell radius.
void CellDivision(vector<cell>& Cells,int& Nc,const float& cellradius,const float& cellcycletime){
  float theta;                      // Angle of division plane
  default_random_engine generator;  // Normal distribution for finding division plane angle
  normal_distribution<double> distribution(0.0,0.01);
  // Loop over all cells in Cells vector.
  for (int ii=0;ii<Nc;ii++){
    // Test age of each cell in turn. If age is greater than cellcycletime, trigger division.
    if (Cells[ii].age>cellcycletime){
      //theta = 2*M_PI*rand()/RAND_MAX;
      // Find division plane angle from normal distribution
      theta = 2*M_PI*distribution(generator);
      // Create new cell
      Cells.push_back(cell(Cells[ii].pos(0)+cellradius*cos(theta),Cells[ii].pos(1)+cellradius*sin(theta)));
      // Update position and age of existing cell.
      Cells[ii].pos(0) = Cells[ii].pos(0)-cellradius*cos(theta);
      Cells[ii].pos(1) = Cells[ii].pos(1)-cellradius*sin(theta);
      Cells[ii].age = 0;
    }else{}
  }
  // Update number of cells Nc
  Nc=Cells.size();
}
